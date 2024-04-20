// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckInfo.h"

void UDeckInfo::CreateMockDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		UCardData* Data1 = NewObject<UCardData>();
		this->SinglePlayerDeck.Add(NewObject<UCardData>("Test 1", "Test 1");
		this->SinglePlayerDeck.Emplace("Test 1", "Test 1");
		this->SinglePlayerDeck.Emplace("Test 2", "Test 2");
		this->SinglePlayerDeck.Emplace("Test 3", "Test 3");
	}
}

TArray<UCardData> UDeckInfo::GetSinglePlayerDeck()
{
	this->CreateMockDeck();
	return this->SinglePlayerDeck; // returns a copy of SinglePlayerDeck
}