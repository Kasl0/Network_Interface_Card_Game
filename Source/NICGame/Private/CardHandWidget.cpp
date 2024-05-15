// Fill out your copyright notice in the Description page of Project Settings.


#include "CardHandWidget.h"
#include <iostream>
#include "Kismet/GameplayStatics.h"

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


