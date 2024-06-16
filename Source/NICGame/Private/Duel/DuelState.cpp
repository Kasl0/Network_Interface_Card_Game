#include "Duel/DuelState.h"
#include "Cards/CardWidget.h"
#include "Duel/EnemyDuelCharacter.h"
#include "Duel/Board/BoardState.h"
#include "Duel/DuelCharacter.h"

UDuelState::UDuelState()
{
	this->BoardState = NewObject<UBoardState>();
	this->BoardState->Init(this, 4);
	this->BoardState->AddToRoot();
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
			Character->AddToRoot();
			Character->InitializeDuelState(this);
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
	this->BoardState->MinionAttack(this->CurrentTurn);
	this->CurrentTurn = this->CurrentTurn == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
}

TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> UDuelState::GetCharacters()
{
	return this->DuelCharacters;
}

bool UDuelState::PlayCard(UCardData* CardData, uint8 Column)
{
	if (this->DuelCharacters[TEnumAsByte(Friendly)]->UseMana(CardData->CardCost))
	{
		return this->BoardState->PlaceCard(CardData, this->CurrentTurn, Column);
	}
	else
	{
		return false;
	}
}

UBoardState* UDuelState::GetBoardState()
{
	return this->BoardState;
}

UEnemyDeckInfo* UDuelState::GetEnemyDeckInfo()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	return Cast<UEnemyDeckInfo>(GameInstance->GetSubsystem<UEnemyDeckInfo>());
}
