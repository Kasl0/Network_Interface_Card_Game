// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Dialogues/EDialogueType.h"
#include "DialogueManager.generated.h"

USTRUCT(BlueprintType)
struct FDialogueRow : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
        int32 ClassID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
        FString Question;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
        TMap<FString, FString> Answers;
};

USTRUCT(BlueprintType)
struct FDialogueOption
{
    GENERATED_BODY()

    // ID dialogu
    UPROPERTY(BlueprintReadOnly)
    int32 ClassID;

    // Tekst dialogu, wyświetlany na górze ekranu
    UPROPERTY(BlueprintReadOnly)
    FString Question;

    // Teksty odpowiedzi
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FString> Answers;

    // Konsekwencje wybrania odpowiedzi
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, FString> Outcomes;

    // ID następnej kwestii dialogowej
    UPROPERTY(BlueprintReadOnly)
    TMap<FString, int32> NextQuestion;

    // Typ dialogu
    UPROPERTY(BlueprintReadOnly);
    TEnumAsByte<EDialogueType> Type;
};

/**
 *
 */
UCLASS(Blueprintable)
class NICGAME_API UDialogueManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    UDialogueManager();

public:
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool LoadDialoguesFromFile(const FString FilePath);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    TArray<FDialogueOption> GetDialogues();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    FDialogueOption GetDialogueById(int32 Id);

    UFUNCTION()
    void HandleDialogueChoice(FDialogueOption Dialogue, FString AnswerKey);

    void CreateDialogueChain(int32 FirstId, TFunction<void()> Callback);

    void CreateQuizChain(int32 Count = 3, TFunction<void(int32)> Callback = nullptr);

private:
    TSubclassOf<UUserWidget> DialogueWidgetClass;

    UPROPERTY()
    TArray<FDialogueOption> Dialogues;

    UFUNCTION()
    void CreateDialogueWidget(int32 Id);

    TFunction<void()> CurrentCallback;

    TFunction<void(int32)> QuizCallback;

    UPROPERTY()
    int32 CorrectAnswers;

    UPROPERTY()
    TArray<int32> QuizIndexes;
};
