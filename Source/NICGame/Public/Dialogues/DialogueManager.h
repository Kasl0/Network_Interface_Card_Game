// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
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
    UPROPERTY(BlueprintReadOnly)
        int32 ClassID;

    UPROPERTY(BlueprintReadOnly)
        FString Question;

    UPROPERTY(BlueprintReadOnly)
        TMap<FString, FString> Answers;
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

    UFUNCTION()
    void CreateDialogueWidget(int32 Id);

private:
    TSubclassOf<UUserWidget> DialogueWidgetClass;

    UPROPERTY()
    TArray<FDialogueOption> Dialogues;
};
