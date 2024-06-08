// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "UObject/Object.h"
#include "DuelCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDuelCharacter : public UObject, public IDamageable
{
	GENERATED_BODY()

	// Character starting health
	int32 BaseHealth;

	// Character health after damage, modifiers etc.
	int32 CurrentHealth;
	
public:
	void Init();
	
	virtual void TakeDamage(int32 DamageValue, UObject* Source) override;
};
