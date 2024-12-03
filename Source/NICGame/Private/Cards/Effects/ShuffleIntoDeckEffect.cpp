// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/ShuffleIntoDeckEffect.h"
#include "Cards/CardService.h"

void UShuffleIntoDeckEffect::Init(int32 Card, int32 Count, UWorld* WorldInstance)
{
	this->CardToShuffleId = Card;
	this->CardCount = Count;
	this->World = WorldInstance;
}

void UShuffleIntoDeckEffect::ApplyShuffle(UBattleDeck* Deck)
{
	UGameInstance* Ins = Cast<UGameInstance>(World->GetGameInstance());
	UCardService* Service = Cast<UCardService>(Ins->GetSubsystem<UCardService>());
	for (int32 i = 0; i < CardCount; i++)
	{
		UCardData* CardToShuffle = Service->GetCardData(CardToShuffleId);
		//CardToShuffle->AddToRoot();
		CardToShuffle->Rename(NULL, World);
		Deck->ShuffleIntoDeck(CardToShuffle);
	}
}
