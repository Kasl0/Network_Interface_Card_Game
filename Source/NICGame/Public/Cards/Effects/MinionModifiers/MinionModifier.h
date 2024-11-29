// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/Effect.h"
#include "UObject/Object.h"
#include "Cards/Effects/MinionModifiers/EModifierType.h"
#include "MinionModifier.generated.h"

/**
 * Base minion modifier for other modifiers to derive from, not meant to be instantiated
 */
UCLASS(Abstract)
class NICGAME_API UMinionModifier : public UEffect
{
	GENERATED_BODY()

public:
	virtual void Init();

	// Add modifier to a minion's modifier list
	virtual void Apply(UObject* EffectTarget) override;

	virtual void ApplyEffect(UObject* EffectTarget);

	TEnumAsByte<EModifierType> Type = Base;
};
