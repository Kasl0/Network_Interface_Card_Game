// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/Effect.h"
#include "Cards/CardTypes/Minion.h"
#include "Duel/Board/BoardState.h"
#include "SummonEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API USummonEffect : public UEffect
{
	GENERATED_BODY()
	
	TSharedPtr<FJsonObject> MinionsToSummonArgs;

	UPROPERTY()
	UWorld* World;

	void SummonMinion(UMinion* Minion, UBoardState* BoardState, EBoardSide Side);

public:
	void Init(TSharedPtr<FJsonObject> args, UWorld* Wrld);

	void ApplySummonEffect(EBoardSide Side);
};
