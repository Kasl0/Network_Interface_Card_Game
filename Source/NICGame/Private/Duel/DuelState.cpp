// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/DuelState.h"


void UDuelState::StartDuel()
{
	// for (EBoardSide Side : {Friendly, Enemy})
	// {
	// 	if (this->DuelCharacters.Contains(Side))
	// 	{
	// 		this->DuelCharacters[Side]->RemoveFromRoot();
	// 		this->DuelCharacters.Remove(Side);
	// 	}
	// 	UDuelCharacter* Character = NewObject<UDuelCharacter>();
	// 	Character->Init();
	// 	Character->AddToRoot();
	// 	this->DuelCharacters.Add(Side, Character);
	// }
	this->CurrentTurn = Friendly;
}

UCardWidget* UDuelState::GetSelectedCard() const
{
	return this->CurrentTurn == Friendly ? SelectedCard : nullptr;
}

void UDuelState::SetSelectedCard(UCardWidget* NewSelectedCard)
{
	this->SelectedCard = NewSelectedCard;
}

void UDuelState::SwitchPlayerTurn()
{
	// Any additional logic surrounding turn change
	this->CurrentTurn = this->CurrentTurn == Friendly ? Enemy : Friendly;
}
