// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/DuelState.h"


void UDuelState::StartDuel()
{
	for (EBoardSide Side : {TEnumAsByte(Friendly), TEnumAsByte(Enemy)})
	{
		if (this->DuelCharacters.Contains(Side))
		{
			this->DuelCharacters[Side]->RemoveFromRoot();
			this->DuelCharacters.Remove(Side);
		}
		UDuelCharacter* Character = NewObject<UDuelCharacter>();
		Character->Init();
		Character->AddToRoot();
		this->DuelCharacters.Add(Side, Character);
	}
	this->CurrentTurn = TEnumAsByte(Friendly);
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
	// Tutaj atakowanie miniona na przeciwko, lub postaci przeciwnika jak nie ma miniona
	this->CurrentTurn = this->CurrentTurn == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
}

TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> UDuelState::GetCharacters()
{
	return this->DuelCharacters;
}

bool UDuelState::PlayCard(UCardData* CardData)
{
	// TODO
	//  Później proponuję przenieść tutaj logikę zagrywania kart z blueprintów
	//  Póki co tylko zarządza maną
	return this->DuelCharacters[TEnumAsByte(Friendly)]->UseMana(CardData->CardCost);
}
