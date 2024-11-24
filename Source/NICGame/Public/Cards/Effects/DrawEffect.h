// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/Effect.h"
#include "DrawEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDrawEffect : public UEffect
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 CardsToDraw;

public:
	void Init(uint32 Value);

	void Apply(UObject* EffectTarget) override;
};
