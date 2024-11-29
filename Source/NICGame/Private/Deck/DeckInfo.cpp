// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck/DeckInfo.h"

#include "Cards/CardTypes/CardData.h"
#include "Cards/CardService.h"
#include "Kismet/GameplayStatics.h"

void UDeckInfo::CreateMockDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		//int32 StartingDeckIds[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }; // maybe add this info to json file? - field "isStartingDeck": true / false to each card
		int32 StartingDeckIds[] = { 1, 10, 11, 15, 18 };

		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		CardService* CardServ = Cast<CardService>(GameInstance->GetSubsystem<CardService>());

		for (int id : StartingDeckIds)
		{
			UCardData* Card = CardServ->GetCardData(id);
			Card->AddToRoot();
			this->SinglePlayerDeck.Add(Card);
		}
	}
}

TArray<UCardData*> UDeckInfo::GetSinglePlayerDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		this->CreateMockDeck();
	}

	DeckCopy.Empty();
	for (int i = 0; i < this->SinglePlayerDeck.Num(); i++)
	{
		UCardData* Card = DuplicateObject(this->SinglePlayerDeck[i], this->GetOuter());
		//Card->AddToRoot();
		DeckCopy.Add(Card);
	}
	return DeckCopy;
}