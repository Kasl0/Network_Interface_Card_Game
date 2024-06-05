// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/UniformGridPanel.h"
#include "CardSlotWidget.h"

void UBoardWidget::NativeConstruct()
{
    Super::NativeConstruct();
	ColumnCount = 4;
}

UCardWidget* UBoardWidget::GetUpcomingCardWidgetAt(uint8 Column)
{
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(UpcomingRow->GetChildAt(Column));
	return CardSlot->GetCardWidget();
}

UCardWidget* UBoardWidget::GetCardWidgetAt(uint8 Row, uint8 Column)
{
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(Battlefield->GetChildAt(Row * ColumnCount + Column));
	return CardSlot->GetCardWidget();
}
