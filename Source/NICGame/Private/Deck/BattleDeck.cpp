// Fill out your copyright notice in the Description page of Project Settings.

#include "Deck/BattleDeck.h"

#include <vector>
#include <chrono>
#include <random>

#include "Deck/DeckInfo.h"
#include "Kismet/GameplayStatics.h"

void UBattleDeck::InitializeDeck(UWorld* World)
{
	UGameInstance* Ins = UGameplayStatics::GetGameInstance(World);
	if (Ins)
	{
		UDeckInfo* DeckInfo = Cast<UDeckInfo>(Ins->GetSubsystem<UDeckInfo>());
		this->CardDataArray = DeckInfo->GetSinglePlayerDeck();

		this->CardOrder = std::vector<int>(this->CardDataArray.Num());
		for (int i = 0; i < this->CardDataArray.Num(); i++)
		{
			CardOrder[i] = i;
		}
		this->RNG = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
		std::ranges::shuffle(std::begin(this->CardOrder), std::end(this->CardOrder), RNG);
	}
}

UCardData* UBattleDeck::DrawCard()
{
	UCardData* LastCard = nullptr;
	if (this->CardOrder.size() > 0)
	{
		LastCard = this->CardDataArray[this->CardOrder.back()];
		//LastCard->AddToRoot();
		this->CardOrder.pop_back();
	}
	// TODO
	//  What to do if deck is empty
	return LastCard;
}

void UBattleDeck::ShuffleIntoDeck(UCardData* Card)
{
	//std::random_device rd;     // Only used once to initialise (seed) engine
	//std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	//std::uniform_int_distribution<int> uni(0, CardDataArray.Num()); // Guaranteed unbiased

	//auto random_integer = uni(rng);

	int32 output = 0 + (rand() % static_cast<int>(this->CardOrder.size() - 0 + 1));

	this->CardDataArray.Add(Card);
	this->CardOrder.insert(this->CardOrder.begin() + output, CardDataArray.Num() - 1); // Insert Card at random position
}
