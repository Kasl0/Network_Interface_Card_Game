#include "Cards/CardHand.h"

void UCardHand::DrawCard()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UBattleDeck* Deck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
	UCardData* NewCardData = Deck->DrawCard();
	if (NewCardData)
	{
		this->AddCardData(NewCardData);
	}
}

UCardData* UCardHand::GetCardDataAt(uint8 Index)
{
	return this->CardDataArray[Index];
}

uint8 UCardHand::GetCardDataCount()
{
	return this->CardDataArray.Num();
}

void UCardHand::AddCardData(UCardData* CardData)
{
	this->CardDataArray.Add(CardData);
	this->BroadcastCardHandAdded(CardData);
}

void UCardHand::RemoveCardData(UCardData* CardData)
{
	this->CardDataArray.Remove(CardData);
	this->BroadcastCardHandRemoved(CardData);
}

void UCardHand::RemoveAllCardData()
{
	for (UCardData* CardData : this->CardDataArray)
	{
		this->RemoveCardData(CardData);
	}
}

void UCardHand::BroadcastCardHandAdded(UCardData* CardData)
{
	this->OnCardHandAdd.Broadcast(CardData);
}

void UCardHand::BroadcastCardHandRemoved(UCardData* CardData)
{
	this->OnCardHandRemove.Broadcast(CardData);
}
