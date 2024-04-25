// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckInfo.h"

void UDeckInfo::CreateMockDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		UCardData* Data1 = NewObject<UCardData>();
		Data1->SetData("Test1", "Test1");
		Data1->AddToRoot();
		this->SinglePlayerDeck.Add(Data1);

		UCardData* Data2 = NewObject<UCardData>();
		Data2->SetData("Test2", "Test2");
		Data2->AddToRoot();
		this->SinglePlayerDeck.Add(Data2);

		UCardData* Data3 = NewObject<UCardData>();
		Data3->SetData("Test3", "Test3");
		Data3->AddToRoot();
		this->SinglePlayerDeck.Add(Data3);
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
		// Nie wiem co tu sie dzieje
		// https://forums.unrealengine.com/t/duplicate-uobject-into-another-one/311521/4
		this->DeckCopy.Add(DuplicateObject(this->SinglePlayerDeck[i], this->GetOuter()));
	}
	return DeckCopy;
}