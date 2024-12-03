// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/Effect.h"
#include "Cards/CardTypes/CardData.h"
#include "Deck/BattleDeck.h"
#include "ShuffleIntoDeckEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UShuffleIntoDeckEffect : public UEffect
{
	GENERATED_BODY()

	UPROPERTY()
	int32 CardToShuffleId;

	UPROPERTY()
	int32 CardCount;

	UPROPERTY()
	UWorld* World;

public:
	void Init(int32 Card, int32 Count, UWorld* WorldInstance);

	void ApplyShuffle(UBattleDeck* Deck);
};
