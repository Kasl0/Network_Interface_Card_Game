#include "Duel/Board/BoardState.h"
#include "Duel/DuelState.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardTypes/Minion.h"
#include "Cards/CardTypes/Spell.h"
#include "Cards/Effects/DrawEffect.h"
#include "Cards/Effects/ShuffleIntoDeckEffect.h"
#include "Cards/Effects/ChooseOneEffect.h"
#include "Cards/Effects/SummonEffect.h"
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

	USpell* Spell = Cast<USpell>(Card);
	if (Spell)
	{
		if (Spell->SpellEffect->Target == Minion)
		{
			if (this->Board[Side * this->ColumnCount + Column] != NULL)
			{
				Spell->Apply(this->Board[Side * this->ColumnCount + Column]);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (UDrawEffect* DrawSpell = Cast<UDrawEffect>(Spell->SpellEffect))
		{
			DrawSpell->Apply(DuelState->GetCharacters()[Friendly]);
			return true;
		}
		else if (UShuffleIntoDeckEffect* ShuffleSpell = Cast<UShuffleIntoDeckEffect>(Spell->SpellEffect))
		{
			UGameInstance* Ins = Cast<UGameInstance>(DuelState->GetWorld()->GetGameInstance());
			UBattleDeck* BattleDeck = Cast<UBattleDeck>(Ins->GetSubsystem<UBattleDeck>());
			ShuffleSpell->ApplyShuffle(BattleDeck);
			return true;
		}
		else if (USummonEffect* SummonSpell = Cast<USummonEffect>(Spell->SpellEffect))
		{
			SummonSpell->ApplySummonEffect(Side);
			return true;
		}
		else if (UChooseOneEffect* ChooseSpell = Cast<UChooseOneEffect>(Spell->SpellEffect))
		{
			ChooseSpell->Apply(NULL, NULL);
			return true;
		}
		else
		{
			Spell->Apply(NULL); // Target not needed
			return true;
		}
	}

	UMinion* Minion = Cast<UMinion>(Card);
	if (Minion != NULL)
	{
		this->Board[Side * this->ColumnCount + Column] = Card;
		this->BroadcastBoardChanged();
		return true;
	}

	return false;
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

void UBoardState::MinionAttack(EBoardSide AttackerSide, TFunction<void()> OnMinionAttackComplete)
{
	this->CurrentAttackerSide = AttackerSide;
	this->CurrentlyAttackingMinion = 0;
	this->AfterMinionAttack = OnMinionAttackComplete;

	this->MinionAttackInColumn();
}

// TODO
//  Bug! Minion atakuje, zanim się przesunie

void UBoardState::MinionAttackInColumn()
{
	if (this->CurrentlyAttackingMinion >= this->ColumnCount) {
		this->OnBoardChanged.Broadcast();
		this->AfterMinionAttack();
	}
	else
	{
		bool AttackAnimationPlayed = false;
		int i = this->CurrentlyAttackingMinion;
		EBoardSide DefenderSide = CurrentAttackerSide == TEnumAsByte(Friendly) ? TEnumAsByte(Enemy) : TEnumAsByte(Friendly);

		// Create a shared pointer to manage the flag
		auto AttackAnimationPlayedPtr = MakeShared<bool>(false);

		// Create the callback using a capture list that uses a shared pointer
		auto Callback = [this, AttackAnimationPlayedPtr]()
			{
				if (!ensure(this != nullptr))
				{
					UE_LOG(LogTemp, Error, TEXT("Invalid 'this' pointer in Callback"));
					return;
				}
				if (!ensure(CurrentWorld != nullptr))
				{
					UE_LOG(LogTemp, Error, TEXT("Invalid CurrentWorld in Callback"));
					return;
				}

				this->CurrentlyAttackingMinion += 1;

				if (*AttackAnimationPlayedPtr)
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
			};

		UMinion* AttackerMinion = Cast<UMinion>(this->GetCardAt(CurrentAttackerSide, i));
		if (AttackerMinion)
		{
			this->OnMinionAttack.Execute(i, CurrentAttackerSide == TEnumAsByte(Friendly) ? 1 : 0);

			// Set the value through the shared pointer
			*AttackAnimationPlayedPtr = true;

			UMinion* DefenderMinion = nullptr;
			TArray<UMinion*> CurrentDefenders;
			for (int32 j = 0; j < ColumnCount; ++j)
			{
				UMinion* Minion = Cast<UMinion>(this->GetCardAt(DefenderSide, j));
				CurrentDefenders.Add(Minion);
				if (!DefenderMinion && Minion && Minion->HasTaunt) DefenderMinion = Minion;
			}
			if (!DefenderMinion) DefenderMinion = CurrentDefenders[i];

			if (DefenderMinion)
			{
				// Attack the minion in front
				AttackerMinion->AttackTarget(DefenderMinion, Callback);
			}
			else
			{
				// Attack the enemy player
				AttackerMinion->AttackTarget(this->DuelState->GetCharacters()[DefenderSide], Callback);
			}
		}
		else
		{
			Callback();
		}
	}
}

void UBoardState::DestroyCard(UCardData* Card, bool Broadcast)
{
	for (int i = 0; i < this->ColumnCount * 2; i++)
	{
		if (this->Board[i] == Card)
		{
			this->Board[i] = NULL;
			if (Broadcast) this->BroadcastBoardChanged();
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
