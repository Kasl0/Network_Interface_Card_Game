// Fill out your copyright notice in the Description page of Project Settings.


#include "CardHandWidget.h"

#include "CardBattleCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCardHandWidget::DrawCard()
{
	if (!this->BattleDeck) 
	{
		ACardBattleCharacter* Ab = Cast<ACardBattleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		this->BattleDeck = Ab->GetBattleDeck();
		this->BattleDeck->InitializeDeck(GetWorld()); 
	}
	UCardData* NewCardData = this->BattleDeck->DrawCard();
	if (NewCardData)
	{
		this->CardDataArray.Add(NewCardData);
		this->CreateCardWidget(NewCardData);
	}
}


