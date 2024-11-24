// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/FriendlyDuelCharacter.h"



void UFriendlyDuelCharacter::StartTurn()
{
	Super::StartTurn();

	this->DrawCard();
}

void UFriendlyDuelCharacter::Init(UWorld* World, int32 Health, int32 Mana)
{
	Super::Init();

	UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
	Hand = Cast<UCardHand>(GameInstance->GetSubsystem<UCardHand>());
	if (Hand->GetCardDataCount() == 0)
	{
		for (int i = 0; i < 3; ++i) this->DrawCard();
	}
}

void UFriendlyDuelCharacter::DrawCard()
{
	if (Hand)
	{
		Hand->DrawCard();
		this->CardDrawInCurrentTurn += 1;
	}
}
