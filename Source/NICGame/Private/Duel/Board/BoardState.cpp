#include "Duel/Board/BoardState.h"

UBoardState::UBoardState()
{
	this->ColumnCount = 4;
	this->UpcomingRow.SetNum(this->ColumnCount);
	this->Board.SetNum(this->ColumnCount *2);
	
	for (int i = 0; i < this->ColumnCount; i++)
	{
		this->UpcomingRow[i] = NULL;
	}
	for (int i = 0; i < this->ColumnCount * 2; i++)
	{
		this->Board[i] = NULL;
	}
	this->BroadcastBoardChanged();
}

UCardData* UBoardState::GetUpcomingCardAt(uint8 Column)
{
	if (Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	return this->UpcomingRow[Column];
}

UCardData* UBoardState::GetCardAt(EBoardSide Side, uint8 Column)
{
	if (Side < 0 || Side >= 2 || Column < 0 || Column >= this->ColumnCount)
	{
		return NULL;
	}
	return this->Board[Side * this->ColumnCount + Column];
}

bool UBoardState::PlaceUpcomingCard(UCardData* Card, uint8 Column)
{
	if (Column < 0 || Column >= this->ColumnCount)
	{
		return false;
	}
	if (this->UpcomingRow[Column] != NULL)
	{
		return false;
	}

	this->UpcomingRow[Column] = Card;
	this->BroadcastBoardChanged();
	return true;
}

bool UBoardState::PlaceCard(UCardData* Card, EBoardSide Side, uint8 Column)
{
	if (Side < 0 || Side >= 2 || Column < 0|| Column >= this->ColumnCount)
	{
		return false;
	}
	if (this->Board[Side * this->ColumnCount + Column] != NULL)
	{
		return false;
	}

	this->Board[Side * this->ColumnCount + Column] = Card;
	this->BroadcastBoardChanged();
	return true;
}

void UBoardState::MoveUpcomingCardsToBattlefield()
{
	bool BoardChanged = false;
	for (int i = 0; i < this->ColumnCount; i++)
	{
		if (this->UpcomingRow[i] != NULL && this->Board[i] == NULL)
		{
			this->Board[i] = this->UpcomingRow[i];
			this->UpcomingRow[i] = NULL;
			BoardChanged = true;
		}
	}
	if (BoardChanged)
	{
		this->BroadcastBoardChanged();
	}
}

void UBoardState::BroadcastBoardChanged()
{
	this->OnBoardChanged.Broadcast();
}
