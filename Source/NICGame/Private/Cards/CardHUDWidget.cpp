// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardHUDWidget.h"
#include "Components/Button.h"
#include <Cards/CardWidget.h>

#include "Cards/CardHandWidget.h"

void UCardHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DrawCardButton)
	{
		DrawCardButton->OnClicked.AddDynamic(this, &UCardHUDWidget::DrawCard);
	}
}


void UCardHUDWidget::DrawCard()
{
	this->CardHand->DrawCard();
}
