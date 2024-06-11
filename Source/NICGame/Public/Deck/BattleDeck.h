// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <random>

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"
#include "UObject/Object.h"
#include "BattleDeck.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UBattleDeck : public UObject
{
	GENERATED_BODY()

protected:
	std::default_random_engine RNG;
	
	UPROPERTY()
	TArray<UCardData*> CardDataArray;

	std::vector<int> CardOrder;

	bool isInitialized = false;

public:
	void InitializeDeck(UWorld* World);

	UCardData* DrawCard();
};
