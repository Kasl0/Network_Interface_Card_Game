// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/MinionModifiers/MinionModifier.h"
#include "Cards/Effects/MinionModifiers/EModifierType.h"
#include "StatModifier.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UStatModifier : public UMinionModifier
{
	GENERATED_BODY()

public:
	void Init(int32 Attack, int32 Health);

	int32 AttackModifier = 0;

	int32 HealthModifier = 0;
};
