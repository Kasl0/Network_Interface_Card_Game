// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/Effect.h"
#include "Cards/CardService.h"
#include "ChooseOneEffect.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UChooseOneEffect : public UEffect
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UCardData*> Cards;

	UPROPERTY()
	UWorld* World;

public:
	void Init(UCardService* CardService, int32 id1, int32 id2, int32 id3);

	void Apply(UObject* EffectTarget, TFunction<void()> AfterChoiceCallback = NULL);
	
};
