// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckInfo.h"

#include "Cards/CardData.h"

void UDeckInfo::CreateMockDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		/*for (int i = 0; i < 5; i++) 
		{
			UCardData* Data = NewObject<UCardData>();
			Data->SetData(std::to_string(i), std::to_string(i));
			Data->AddToRoot();
			this->SinglePlayerDeck.Add(Data);
		}*/
	}
}

TArray<UCardData*> UDeckInfo::GetSinglePlayerDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		this->CreateMockDeck();
	}

	for (int i = 0; i < this->SinglePlayerDeck.Num(); i++)
	{
		this->DeckCopy.Add(DuplicateObject(this->SinglePlayerDeck[i], this->GetOuter()));
	}
	return DeckCopy;
}