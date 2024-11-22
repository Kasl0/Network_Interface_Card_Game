// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
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
    UFUNCTION(BlueprintCallable)
        void InitializeAnswers(const TMap<FString, FString>& Answers);
    UFUNCTION(BlueprintCallable)
        void OnAnswerClicked();

protected:
    // VerticalBox, do którego dodasz przyciski
    UPROPERTY(meta = (BindWidget))
        UVerticalBox* AnswersBox;
	
};
