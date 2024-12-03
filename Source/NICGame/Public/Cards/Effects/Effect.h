// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cards/Effects/EffectTarget.h"
#include "Effect.generated.h"

/**
 * Base class for all effects
 */
UCLASS(Abstract)
class NICGAME_API UEffect : public UObject
{
	GENERATED_BODY()
public:
	
	virtual void Apply(UObject* Target);

	UPROPERTY()
	TEnumAsByte<EEffectTarget> Target = NoTarget;
};
