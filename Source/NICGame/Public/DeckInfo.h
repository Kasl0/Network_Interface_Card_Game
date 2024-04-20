// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DeckInfo.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDeckInfo : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	TArray<UCardData> SinglePlayerDeck;

	void CreateMockDeck();

public:
	TArray<UCardData> GetSinglePlayerDeck();
};
