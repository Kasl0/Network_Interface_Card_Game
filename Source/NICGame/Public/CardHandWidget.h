// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleDeck.h"
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
	TArray<UCardData*> CardDataArray;
	
	UBattleDeck* BattleDeck;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateCardWidget(UCardData* CardData);
	
public:
	void DrawCard();
};
