#include "Duel/Board/BoardState.h"
#include "Duel/DuelState.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardTypes/Minion.h"
#include "Cards/CardTypes/Spell.h"
#include "Duel/DuelCharacter.h"

#include "Async/Async.h"

void UBoardState::Init(UDuelState* State, uint8 ColumnCnt, UWorld* World)
{
	this->DuelState = State;
	this->ColumnCount = ColumnCnt;
	this->CurrentWorld = World;
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

	this->OnBoardReset.Broadcast();
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
		/*AsyncTask(ENamedThreads::GameThread, [&]() {
			this->OnMinionMove.Broadcast();
		});*/
		this->OnMinionMove.Execute();
	}
}

void UBoardState::MinionAttack(EBoardSide AttackerSide, TFunction<void(EBoardSide EndingTurn)> OnMinionAttackComplete)
{
	this->CurrentAttackerSide = AttackerSide;
	this->CurrentlyAttackingMinion = 0;
	this->AfterMinionAttack = OnMinionAttackComplete;
	this->MinionAttackInColumn();
	/*FTimerHandle MinionAttackHandle;
	this->CurrentWorld->GetTimerManager().SetTimer(
		MinionAttackHandle,
		this,
		&UBoardState::MinionAttackInColumn,
		0.2f,
		false
	);*/
}

// TODO
//  Bug! Minion atakuje, zanim się przesunie

void UBoardState::MinionAttackInColumn()
{
	bool AttackAnimationPlayed = false;

	int i = this->CurrentlyAttackingMinion;
	EBoardSide DefenderSide = CurrentAttackerSide == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);

	UCardData* Attacker = this->GetCardAt(CurrentAttackerSide, i);
	if (Attacker != NULL)
	{

		UMinion* AttackerMinion = Cast<UMinion>(Attacker);
		if (AttackerMinion != NULL)
		{
			/*AsyncTask(ENamedThreads::GameThread, [this, i]() {
				this->OnMinionAttack.Execute(i, CurrentAttackerSide == TEnumAsByte(Friendly) ? 1 : 0);
			});*/

			this->OnMinionAttack.Execute(i, CurrentAttackerSide == TEnumAsByte(Friendly) ? 1 : 0);
			AttackAnimationPlayed = true;

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
	}

	this->CurrentlyAttackingMinion += 1;
	if (this->CurrentlyAttackingMinion < this->ColumnCount) {
		if (AttackAnimationPlayed)
		{
			FTimerHandle MinionAttackHandle;
			this->CurrentWorld->GetTimerManager().SetTimer(
				MinionAttackHandle,
				this,
				&UBoardState::MinionAttackInColumn,
				0.2f,
				false
			);
		}
		else this->MinionAttackInColumn();
	}
	else {
		this->BroadcastBoardChanged();
		FTimerHandle MinionAttackHandle;
		this->AfterMinionAttack(CurrentAttackerSide);
	}
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

bool UBoardState::IsBoardSideFull(EBoardSide Side)
{
	for (int i = 0; i < this->ColumnCount; i++)
	{
		if (this->Board[Side * this->ColumnCount + i] == NULL)
		{
			return false;
		}
	}
	return true;
}

bool UBoardState::IsBoardSideEmpty(EBoardSide Side)
{
	for (int i = 0; i < this->ColumnCount; i++)
	{
		if (this->Board[Side * this->ColumnCount + i] != NULL)
		{
			return false;
		}
	}
	return true;
}

void UBoardState::BroadcastBoardChanged()
{
	/*AsyncTask(ENamedThreads::GameThread, [&]() {
		this->OnBoardChanged.Broadcast();
	});*/
	this->OnBoardChanged.Broadcast();
}
