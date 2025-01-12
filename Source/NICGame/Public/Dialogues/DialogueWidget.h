// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "DialogueManager.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // Funkcja do inicjalizacji odpowiedzi
    UFUNCTION(BlueprintImplementableEvent)
    void InitializeAnswers();

    UFUNCTION(BlueprintCallable)
    void OnAnswerClicked(FString AnswerKey);

    UFUNCTION(BlueprintCallable)
    void SetDialogue(FDialogueOption NewDialogue);

    UPROPERTY()
    UDialogueManager* DialogueManager;

protected:

    UPROPERTY(BlueprintReadWrite)
    FDialogueOption Dialogue;
	
};
