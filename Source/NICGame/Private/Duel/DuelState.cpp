// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/DuelState.h"


void UDuelState::StartDuel()
{
	for (EBoardSide Side : {Friendly, Enemy})
	{
		if (this->DuelCharacters[Side])
		{
			this->DuelCharacters[Side]->RemoveFromRoot();
		}
		this->DuelCharacters[Side] = NewObject<UDuelCharacter>();
		this->DuelCharacters[Side]->Init();
		this->DuelCharacters[Side]->AddToRoot();
	}
}

UCardWidget* UDuelState::GetSelectedCard() const
{
	return SelectedCard;
}

void UDuelState::SetSelectedCard(UCardWidget* NewSelectedCard)
{
	SelectedCard = NewSelectedCard;
}

void UDuelState::SwitchTurn()
{
	// Any additional logic surrounding turn change
	this->CurrentTurn = static_cast<EBoardSide>(1 - this->CurrentTurn);
}
