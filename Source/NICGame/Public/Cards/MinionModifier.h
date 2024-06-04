// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/Effect.h"
#include "UObject/Object.h"
#include "MinionModifier.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UMinionModifier : public UObject
{
	GENERATED_BODY()

public:
	uint32 AttackModifier = 0;

	int32 HealthModifier = 0;

	UEffect* Effect = nullptr;
	
	// How long the modifier lasts (-1 means no limit)
	int32 TurnsLeft = -1;
};
