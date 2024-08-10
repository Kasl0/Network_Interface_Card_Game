#include "Duel/Board/BoardWidget.h"
#include "Duel/DuelState.h"
#include "Duel/Board/CardSlotWidget.h"
#include "Duel/Board/UpcomingCardSlotWidget.h"
#include "Cards/CardWidget.h"
#include "Cards/CardTypes/CardData.h"

void UBoardWidget::NativeConstruct()
{
    Super::NativeConstruct();

	ColumnCount = 4;

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	this->BoardState = DuelState->GetBoardState();

	this->BoardState->OnBoardChanged.AddDynamic(this, &UBoardWidget::OnBoardChanged);
	this->BoardState->OnMinionAttack.BindDynamic(this, &UBoardWidget::OnMinionAttack);
}

void UBoardWidget::OnBoardChanged()
{
	// Update upcoming row
	for (uint8 Column = 0; Column < this->ColumnCount; Column++)
	{
		UCardData* CardData = this->BoardState->GetUpcomingCardAt(Column);
		UCardWidget* CardWidget = GetUpcomingCardWidgetAt(Column);
		if (CardData != NULL && CardWidget == NULL)
		{
			this->CreateUpcomingCardWidgetAt(Column, CardData);
		}
		else if (CardData == NULL && CardWidget != NULL)
		{
			this->RemoveUpcomingCardWidgetAt(Column);
		}
	}

	// Update battlefield
	for (uint8 Row = 0; Row < 2; Row++)
	{
		for (uint8 Column = 0; Column < this->ColumnCount; Column++)
		{
			UCardData* CardData = this->BoardState->GetCardAt((EBoardSide)Row, Column);
			UCardWidget* CardWidget = GetCardWidgetAt(Row, Column);
			if (CardData != NULL && CardWidget == NULL)
			{
				this->CreateCardWidgetAt(Row, Column, CardData);
			}
			else if (CardData == NULL && CardWidget != NULL)
			{
				this->RemoveCardWidgetAt(Row, Column);
			}
		}
	}
}

UCardWidget* UBoardWidget::GetUpcomingCardWidgetAt(uint8 Column)
{
	if (Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	UUpcomingCardSlotWidget* UpcomingCardSlot = Cast<UUpcomingCardSlotWidget>(UpcomingRow->GetChildAt(Column));
	return UpcomingCardSlot->GetCardWidget();
}

UCardWidget* UBoardWidget::GetCardWidgetAt(uint8 Row, uint8 Column)
{
	if (Row < 0 || Row >= 2 || Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	UCardSlotWidget* CardSlot = Cast<UCardSlotWidget>(Battlefield->GetChildAt(Row * ColumnCount + Column));
	return CardSlot->GetCardWidget();
}
