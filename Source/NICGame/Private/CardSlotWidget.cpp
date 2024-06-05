// Fill out your copyright notice in the Description page of Project Settings.


#include "CardSlotWidget.h"

void UCardSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

	CardWidget = NULL;
}

bool UCardSlotWidget::IsOccupied()
{
	return CardWidget != NULL;
}

UCardWidget* UCardSlotWidget::GetCardWidget()
{
	return CardWidget;
}

void UCardSlotWidget::SetCardWidget(UCardWidget* NewCardWidget)
{
	CardWidget = NewCardWidget;
}

void UCardSlotWidget::OnCardSlotClicked()
{
	if (CardWidget != NULL)
	{
		// place card in battlefield
		// TODO: implement
	}
}
