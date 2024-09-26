#include "Duel/Board/BoardWidgetWithActors.h"
#include "Duel/DuelState.h"
#include "Duel/Board/CardSlotWidgetWithActors.h"
#include "Duel/Board/UpcomingCardSlotWidgetWithActors.h"
#include "Cards/CardWidget.h"
#include "Cards/CardTypes/CardData.h"

void UBoardWidgetWithActors::NativeConstruct()
{
    Super::NativeConstruct();

	ColumnCount = 4;

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());

	//DuelState->SetBoardWidget(this);
	this->BoardState = DuelState->GetBoardState();

	this->BoardState->OnMinionMove.AddDynamic(this, &UBoardWidgetWithActors::OnMoveMinion);
	this->BoardState->OnBoardChanged.AddDynamic(this, &UBoardWidgetWithActors::OnBattlefieldChanged);
	this->BoardState->OnMinionAttack.BindDynamic(this, &UBoardWidgetWithActors::OnMinionAttack);
	this->BoardState->OnBoardReset.AddDynamic(this, &UBoardWidgetWithActors::OnBoardReset);
}

void UBoardWidgetWithActors::OnMoveMinion()
{
	this->ColumnToMoveMinionFrom = 0;
	FTimerHandle MoveMinionHandle;
	GetWorld()->GetTimerManager().SetTimer(
		MoveMinionHandle,
		this,
		&UBoardWidgetWithActors::MoveFromUpcomingRow,
		0.2f,
		false
	);
}

void UBoardWidgetWithActors::OnBoardReset()
{
	for (int i = 0; i < this->ColumnCount; i++)
	{
		this->RemoveUpcomingCardAt(i);
	}
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < this->ColumnCount; i++)
		{
			this->RemoveCardAt(j, i);
		}
	}
}

void UBoardWidgetWithActors::MoveFromUpcomingRow()
{
	bool MoveAnimationPlayed = false;

	UCardData* CardData = this->BoardState->GetUpcomingCardAt(this->ColumnToMoveMinionFrom);
	ACardActor* CardWidget = GetUpcomingCardAt(this->ColumnToMoveMinionFrom);
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
				&UBoardWidgetWithActors::MoveFromUpcomingRow,
				0.2f,
				false
			);
		}
		else this->MoveFromUpcomingRow();
	}
}

void UBoardWidgetWithActors::OnBattlefieldChanged()
{
	// Update upcoming row
	for (uint8 Column = 0; Column < this->ColumnCount; Column++)
	{
		UCardData* CardData = this->BoardState->GetUpcomingCardAt(Column);
		ACardActor* CardWidget = GetUpcomingCardAt(Column);
		if (CardData != NULL && CardWidget == NULL)
		{
			this->CreateUpcomingCardAt(Column, CardData);
		}
	}

	// Update minions on board
	for (uint8 Row = 0; Row < 2; Row++)
	{
		for (uint8 Column = 0; Column < this->ColumnCount; Column++)
		{
			UCardData* CardData = this->BoardState->GetCardAt((EBoardSide)Row, Column);
			ACardActor* CardWidget = GetCardAt(Row, Column);
			// Only on row 1, because spawning enemy cards is already handled by moving from upcoming row
			if (Row == 1 && CardData != NULL && CardWidget == NULL)
			{
				this->CreateCardAt(Row, Column, CardData);
			}
			else if (CardData == NULL && CardWidget != NULL)
			{
				this->RemoveCardAt(Row, Column);
			}
		}
	}
}

ACardActor* UBoardWidgetWithActors::GetUpcomingCardAt(uint8 Column)
{
	if (Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	UUpcomingCardSlotWidgetWithActors* UpcomingCardSlot = Cast<UUpcomingCardSlotWidgetWithActors>(UpcomingRow->GetChildAt(Column));
	return UpcomingCardSlot->GetCard();
}

ACardActor* UBoardWidgetWithActors::GetCardAt(uint8 Row, uint8 Column)
{
	if (Row < 0 || Row >= 2 || Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	UCardSlotWidgetWithActors* CardSlot = Cast<UCardSlotWidgetWithActors>(Battlefield->GetChildAt(Row * ColumnCount + Column));
	return CardSlot->GetCard();
}
