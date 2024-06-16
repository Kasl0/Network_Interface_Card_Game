#include "Duel/Board/BoardState.h"
#include "Duel/DuelState.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardTypes/Minion.h"
#include "Cards/CardTypes/Spell.h"
#include "Duel/DuelCharacter.h"

void UBoardState::Init(UDuelState* State, uint8 ColumnCnt)
{
	this->DuelState = State;
	this->ColumnCount = ColumnCnt;
	this->UpcomingRow.SetNum(this->ColumnCount);
	this->Board.SetNum(this->ColumnCount * 2);

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
		// if spell
		USpell* Spell = Cast<USpell>(Card);
		if (Spell != NULL)
		{
			Spell->Apply(this->Board[Side * this->ColumnCount + Column]);
			return true;
		}
		return false;
	}
	else {
		// if minion
		UMinion* Minion = Cast<UMinion>(Card);
		if (Minion != NULL)
		{
			this->Board[Side * this->ColumnCount + Column] = Card;
			this->BroadcastBoardChanged();
			return true;
		}
		return false;
	}
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

void UBoardState::MinionAttack(EBoardSide AttackerSide)
{
	EBoardSide DefenderSide = AttackerSide == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);
	for (int i = 0; i < this->ColumnCount; i++)
	{
		UCardData* Attacker = this->GetCardAt(AttackerSide, i);
		if (Attacker == NULL)
		{
			continue;
		}
		UMinion* AttackerMinion = Cast<UMinion>(Attacker);
		if (AttackerMinion == NULL)
		{
			continue;
		}

		UCardData* Defender = this->GetCardAt(DefenderSide, i);
		UMinion* DefenderMinion = Cast<UMinion>(Defender);
		if (Defender != NULL && DefenderMinion != NULL)
		{
			// Attack the minion in front
			DefenderMinion->TakeDamage(AttackerMinion->GetAttack(), AttackerMinion);
		}
		else
		{
			// Attack the enemy player
			this->DuelState->GetCharacters()[DefenderSide]->TakeDamage(AttackerMinion->GetAttack(), AttackerMinion);
		}
	}
	this->BroadcastBoardChanged();
}

void UBoardState::DestroyCard(UCardData* Card)
{
	for (int i = 0; i < this->ColumnCount * 2; i++)
	{
		if (this->Board[i] == Card)
		{
			this->Board[i] = NULL;
			this->BroadcastBoardChanged();
			return;
		}
	}
}

uint8 UBoardState::GetColumnCount()
{
	return this->ColumnCount;
}

void UBoardState::BroadcastBoardChanged()
{
	this->OnBoardChanged.Broadcast();
}
