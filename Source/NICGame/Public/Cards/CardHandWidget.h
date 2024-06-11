// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck/BattleDeck.h"
#include "CardWidget.h"
#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHandWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<UCardData*> CardDataArray;
	
	UPROPERTY()
	UBattleDeck* BattleDeck;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateCardWidget(UCardData* CardData);

	UFUNCTION(BlueprintCallable)
	void RemoveCardData(UCardData* CardData);
	
public:
	void DrawCard();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveCard(UCardWidget* CardWidget);
};
