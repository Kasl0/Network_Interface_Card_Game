#include "Duel/DuelState.h"
#include "Duel/EnemyDuelCharacter.h"

UDuelState::UDuelState()
{
	this->BoardState = NewObject<UBoardState>();
}

void UDuelState::StartDuel(EBoardSide StartingSide)
{
	for (EBoardSide Side : {TEnumAsByte(Friendly), TEnumAsByte(Enemy)})
	{
		if (this->DuelCharacters.Contains(Side))
		{
			this->DuelCharacters[Side]->RemoveFromRoot();
			this->DuelCharacters.Remove(Side);
		}

		if (Side == TEnumAsByte(Enemy)) {
			UEnemyDuelCharacter* Character = NewObject<UEnemyDuelCharacter>();
			Character->Init();
			Character->InitializeDuelState(this);
			Character->AddToRoot();
			this->DuelCharacters.Add(Side, Character);
		}
		else {
			UDuelCharacter* Character = NewObject<UDuelCharacter>();
			Character->Init();
			Character->AddToRoot();
			this->DuelCharacters.Add(Side, Character);
		}
	}
	this->CurrentTurn = StartingSide;
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
}

UCardWidget* UDuelState::GetSelectedCard() const
{
	return this->CurrentTurn == TEnumAsByte(Friendly) ? SelectedCard : nullptr;
}

void UDuelState::SetSelectedCard(UCardWidget* NewSelectedCard)
{
	this->SelectedCard = NewSelectedCard;
}

void UDuelState::SwitchPlayerTurn()
{
	this->CurrentTurn = this->CurrentTurn == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
	// Tutaj atakowanie miniona na przeciwko, lub postaci przeciwnika jak nie ma miniona
}

TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> UDuelState::GetCharacters()
{
	return this->DuelCharacters;
}

bool UDuelState::PlayCard(UCardData* CardData, uint8 Column)
{
	this->BoardState->PlaceCard(CardData, this->CurrentTurn, Column);
	return this->DuelCharacters[TEnumAsByte(Friendly)]->UseMana(CardData->CardCost);
}
