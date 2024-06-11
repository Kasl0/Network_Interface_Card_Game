// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Duel/DuelState.h"
#include "Cards/CardHandWidget.h"
#include "CardHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void DrawCard();

	UFUNCTION()
	void EndTurn();

	UPROPERTY()
	UDuelState* DuelState;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* DrawCardButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* EndTurnButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCardHandWidget* CardHand;
};
