// Fill out your copyright notice in the Description page of Project Settings.


#include "CardHUDWidget.h"
#include "Components/Button.h"
#include <CardWidget.h>

#include "CardHandWidget.h"

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
