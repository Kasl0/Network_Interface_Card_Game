// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/MinionModifiers/MinionModifier.h"
#include "OnAttackModifier.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UOnAttackModifier : public UMinionModifier
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool TakesCallback = false;

	UPROPERTY()
	UEffect* EffectAfterAttack;

	void Init(UEffect* Effect);

	void ApplyEffect(UObject* Target, TFunction<void()> Callback);
};
