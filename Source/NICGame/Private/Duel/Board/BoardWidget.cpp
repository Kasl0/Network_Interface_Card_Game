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

	DuelState->SetBoardWidget(this);
	this->BoardState = DuelState->GetBoardState();

	this->BoardState->OnMinionMove.AddDynamic(this, &UBoardWidget::OnMoveMinion);
	this->BoardState->OnBoardChanged.AddDynamic(this, &UBoardWidget::OnBattlefieldChanged);
	this->BoardState->OnMinionAttack.BindDynamic(this, &UBoardWidget::OnMinionAttack);
	this->BoardState->OnBoardReset.AddDynamic(this, &UBoardWidget::OnBoardReset);
}

void UBoardWidget::OnMoveMinion()
{
	this->ColumnToMoveMinionFrom = 0;
	FTimerHandle MoveMinionHandle;
	GetWorld()->GetTimerManager().SetTimer(
		MoveMinionHandle,
		this,
		&UBoardWidget::MoveFromUpcomingRow,
		0.2f,
		false
	);
}

void UBoardWidget::OnBoardReset()
{
	for (int i = 0; i < this->ColumnCount; i++)
	{
		this->RemoveUpcomingCardWidgetAt(i);
	}
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < this->ColumnCount; i++)
		{
			this->RemoveCardWidgetAt(j, i);
		}
	}
}

void UBoardWidget::MoveFromUpcomingRow()
{
	bool MoveAnimationPlayed = false;

	UCardData* CardData = this->BoardState->GetUpcomingCardAt(this->ColumnToMoveMinionFrom);
	UCardWidget* CardWidget = GetUpcomingCardWidgetAt(this->ColumnToMoveMinionFrom);
	if (CardData == NULL && CardWidget != NULL)
	{
		this->MoveUpcomingCardToBoard(this->ColumnToMoveMinionFrom);
		MoveAnimationPlayed = true;
	}

	this->ColumnToMoveMinionFrom += 1;
	if (this->ColumnToMoveMinionFrom < this->ColumnCount)
	{
		if (MoveAnimationPlayed)
		{
			FTimerHandle MoveMinionHandle;
			GetWorld()->GetTimerManager().SetTimer(
				MoveMinionHandle,
				this,
				&UBoardWidget::MoveFromUpcomingRow,
				0.2f,
				false
			);
		}
		else this->MoveFromUpcomingRow();
	}
}

void UBoardWidget::OnBattlefieldChanged()
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
	}

	// Update minions on board
	for (uint8 Row = 0; Row < 2; Row++)
	{
		for (uint8 Column = 0; Column < this->ColumnCount; Column++)
		{
			UCardData* CardData = this->BoardState->GetCardAt((EBoardSide)Row, Column);
			UCardWidget* CardWidget = GetCardWidgetAt(Row, Column);
			// Only on row 1, because spawning enemy cards is already handled by moving from upcoming row
			if (Row == 1 && CardData != NULL && CardWidget == NULL)
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
