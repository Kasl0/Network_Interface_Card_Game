// Fill out your copyright notice in the Description page of Project Settings.


#include "CardHandWidget.h"

#include "CardBattleCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCardHandWidget::NativeConstruct()
{
	this->BattleDeck = Cast<ACardBattleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetBattleDeck();
}

void UCardHandWidget::DrawCard()
{
	UCardData* NewCardData = this->BattleDeck->DrawCard();
	this->CardDataArray.Add(NewCardData);
}


