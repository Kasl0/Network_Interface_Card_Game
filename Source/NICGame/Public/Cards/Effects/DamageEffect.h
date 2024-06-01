// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "DamageEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDamageEffect : public UEffect
{
	GENERATED_BODY()

	UDamageEffect();

	UDamageEffect(uint32 DamageValue);

	uint32 DamageValue;

public:
	void Apply(UObject* EffectTarget) override;
};
