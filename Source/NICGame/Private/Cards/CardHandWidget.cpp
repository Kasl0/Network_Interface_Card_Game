// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardHandWidget.h"

#include "Deck/BattleDeck.h"


void UCardHandWidget::RemoveCardData(UCardData* CardData)
{
	this->CardDataArray.Remove(CardData);
}

void UCardHandWidget::DrawCard()
{
	if (!this->BattleDeck) 
	{
		this->BattleDeck = NewObject<UBattleDeck>();
		this->BattleDeck->AddToRoot();
		this->BattleDeck->InitializeDeck(GetWorld()); 
	}
	UCardData* NewCardData = this->BattleDeck->DrawCard();
	if (NewCardData)
	{
		this->CardDataArray.Add(NewCardData);
		this->CreateCardWidget(NewCardData);
	}
}


