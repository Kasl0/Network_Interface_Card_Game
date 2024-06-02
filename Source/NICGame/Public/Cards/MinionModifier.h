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

	UMinionModifier(const FObjectInitializer& ObjectInitializer);

	UMinionModifier(uint32 Attack=0, int32 Health=0, UEffect* Effect = nullptr, int32 Turns=-1);
	
public:
	uint32 AttackModifier;

	int32 HealthModifier;

	UEffect* Effect;
	
	// How long the modifier lasts (-1 means no limit)
	int32 TurnsLeft;
};
