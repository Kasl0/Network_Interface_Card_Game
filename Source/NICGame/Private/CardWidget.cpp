// Fill out your copyright notice in the Description page of Project Settings.


#include "CardWidget.h"
#include "Components/TextBlock.h"


void UCardWidget::SetName(FText Name) const
{
	if (CardName)
	{
		CardName->SetText(Name);
	}
}

void UCardWidget::SetDescription(FText Description) const
{
	if (CardDescription)
	{
		CardDescription->SetText(Description);
	}
}
