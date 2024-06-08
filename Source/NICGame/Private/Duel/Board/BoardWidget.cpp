// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/Board/BoardWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/UniformGridPanel.h"
#include "Duel/Board/CardSlotWidget.h"

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

void UBoardWidget::SetUpcomingCardWidgetAt(uint8 Column, UCardWidget* CardWidget)
{
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(UpcomingRow->GetChildAt(Column));
	CardSlot->SetCardWidget(CardWidget);
}

void UBoardWidget::MoveUpcomingCardsToBattlefield()
{
	for (uint8 Column = 0; Column < ColumnCount; Column++)
	{
		UCardWidget* CardWidget = GetUpcomingCardWidgetAt(Column);
		if (CardWidget != NULL)
		{
			SetUpcomingCardWidgetAt(Column, NULL);
			SetCardWidgetAt(0, Column, CardWidget);
		}
	}
}


UCardWidget* UBoardWidget::GetCardWidgetAt(uint8 Row, uint8 Column)
{
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(Battlefield->GetChildAt(Row * ColumnCount + Column));
	return CardSlot->GetCardWidget();
}

void UBoardWidget::SetCardWidgetAt(uint8 Row, uint8 Column, UCardWidget* CardWidget)
{
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(Battlefield->GetChildAt(Row * ColumnCount + Column));
	CardSlot->SetCardWidget(CardWidget);
}
