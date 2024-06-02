// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "Cards/CardData.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UMinion : public UCardData, public IDamageable
{
	GENERATED_BODY()
 
	int32 BaseAttack;

	int32 BaseHealth;

	int32 CurrentHealth;

public:	
	void SetData(uint8 Cost, std::string Name, std::string Description, int32 Attack, int32 Health);

	// Get Attack value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetAttack();

	// Get current Health value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth();

	void TakeDamage(int32 DamageValue) override;
};
