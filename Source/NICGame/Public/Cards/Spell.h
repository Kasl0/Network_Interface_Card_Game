// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "Effects/Effect.h"
#include "Spell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API USpell : public UCardData
{
	GENERATED_BODY()
	
	UEffect* SpellEffect;
	
public:
	void init(UEffect* Effect);

	UFUNCTION(BlueprintCallable)
	void Apply(UObject* SpellTarget);
};
