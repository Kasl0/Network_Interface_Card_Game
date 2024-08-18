#include "Cards/CardHand.h"
#include "Duel/DuelState.h"
#include "Duel/DuelCharacter.h"

void UCardHand::DrawCard()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	UDuelCharacter* FriendlyCharacter = DuelState->GetCharacters()[TEnumAsByte(Friendly)];

	// Check if the player has already drawn a card in the current turn
	if (FriendlyCharacter->GetCardDrawInCurrentTurn() > 0)
	{
		return;
	}

	UBattleDeck* Deck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
	UCardData* NewCardData = Deck->DrawCard();
	if (NewCardData)
	{
		this->AddCardData(NewCardData);

		// Increment card draw count for the current turn
		FriendlyCharacter->SetCardDrawInCurrentTurn(FriendlyCharacter->GetCardDrawInCurrentTurn() + 1);
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
