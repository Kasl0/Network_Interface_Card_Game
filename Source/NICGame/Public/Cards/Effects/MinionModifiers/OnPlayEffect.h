// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/MinionModifiers/MinionModifier.h"
#include "OnPlayEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UOnPlayEffect : public UMinionModifier
{
	GENERATED_BODY()

	UEffect* Effect;

public:
	void Init(UEffect* OnPlayEffect);
	
	virtual void Apply(UObject* EffectTarget) override;
};
