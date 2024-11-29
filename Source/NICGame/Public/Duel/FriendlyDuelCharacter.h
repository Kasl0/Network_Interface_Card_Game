// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Duel/DuelCharacter.h"
#include "FriendlyDuelCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UFriendlyDuelCharacter : public UDuelCharacter
{
	GENERATED_BODY()
	
	UPROPERTY()
	UCardHand* Hand;

public:
	UFUNCTION()
	void StartTurn() override;

	UFUNCTION()
	void Init(UWorld* World, int32 Health = 30, int32 Mana = 0);

	UFUNCTION()
	void DrawCard();
};
