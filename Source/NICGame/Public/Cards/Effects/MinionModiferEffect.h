// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "Cards/Effects/MinionModifier.h"
#include "MinionModiferEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UMinionModiferEffect : public UEffect
{
	GENERATED_BODY()

	UMinionModifier* Modifier;

public:
	void Init(UMinionModifier* MinionModifier);
	
	virtual void Apply(UObject* EffectTarget) override;
};
