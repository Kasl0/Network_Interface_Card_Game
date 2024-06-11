// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardHUDWidget.h"
#include "Components/Button.h"
#include <Cards/CardWidget.h>

#include "Cards/CardHandWidget.h"
#include "Duel/DuelState.h"

void UCardHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (this->DrawCardButton)
	{
		this->DrawCardButton->OnClicked.AddDynamic(this, &UCardHUDWidget::DrawCard);
	}

	if (this->EndTurnButton)
	{
		this->EndTurnButton->OnClicked.AddDynamic(this, &UCardHUDWidget::EndTurn);
	}

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		this->DuelState = GameInstance->GetSubsystem<UDuelState>();
		if (this->DuelState)
		{
			//this->DuelState->AddToRoot();
			this->DuelState->StartDuel();
		}
	}
}


void UCardHUDWidget::DrawCard()
{
	this->CardHand->DrawCard();
}

void UCardHUDWidget::EndTurn()
{
	if (this->DuelState)
	{
		this->DuelState->SwitchPlayerTurn();
	}
}
