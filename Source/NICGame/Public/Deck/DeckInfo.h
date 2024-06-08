// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"
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
	UPROPERTY(BlueprintReadOnly)
	TArray<UCardData*> SinglePlayerDeck;

	TArray<UCardData*> DeckCopy;

	void CreateMockDeck();

public:
	TArray<UCardData*> GetSinglePlayerDeck();
};
