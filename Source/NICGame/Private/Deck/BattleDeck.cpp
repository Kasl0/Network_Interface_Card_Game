// Fill out your copyright notice in the Description page of Project Settings.

#include "Deck/BattleDeck.h"

#include <vector>
#include <chrono>

#include "Deck/DeckInfo.h"
#include "Kismet/GameplayStatics.h"

void UBattleDeck::InitializeDeck(UWorld* World)
{
	if (!this->isInitialized)
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

			this->isInitialized = true;
		}
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
