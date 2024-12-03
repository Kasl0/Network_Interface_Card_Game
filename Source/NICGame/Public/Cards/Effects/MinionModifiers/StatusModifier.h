// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/Effects/MinionModifiers/MinionModifier.h"
#include "StatusModifier.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UStatusModifier : public UMinionModifier
{
	GENERATED_BODY()
	
public:
	void Init(bool Poison = false, bool Taunt = false);

	void SetPoison(bool Poison);

	void SetTaunt(bool Taunt);

	bool applyPoison = false; // If this minion deals damage to another minion, kill the target instantly

	bool applyTaunt = false; // Enemy minions have to attack it


};
