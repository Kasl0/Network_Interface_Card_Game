#include "Duel/EnemyDuelCharacter.h"
#include "Duel/Board/BoardState.h"
#include "Duel/EBoardSide.h"

void UEnemyDuelCharacter::InitializeDuelState(UDuelState* State)
{
	this->DuelState = State;
}

void UEnemyDuelCharacter::StartTurn()
{
	Super::StartTurn();
	this->PlayCards();
	this->EndTurn();
}

void UEnemyDuelCharacter::PlayCards()
{
	UBoardState* BoardState = this->DuelState->GetBoardState();

	// Move upcoming cards to the board
	BoardState->MoveUpcomingCardsToBattlefield();

	uint8 Column = this->GetPreferredEmptyColumn();
	if (Column == -1)
	{
		return;
	}

	// One hard-coded enemy for now
	UMinion* Minion1 = NewObject<UMinion>();
	uint8 Cost = 1;
	std::string Name = "Enemy Minion";
	std::string Description = "Very strong enemy, OMG!";
	int32 Attack = FMath::RandRange(1, 3);
	int32 Health = FMath::RandRange(1, 3);
	Minion1->Init(Cost, Name, Description, Attack, Health);
	Minion1->AddToRoot();
	
	// Place the card
	this->DuelState->GetBoardState()->PlaceUpcomingCard(Minion1, Column);
}

uint8 UEnemyDuelCharacter::GetPreferredEmptyColumn()
{
	UBoardState* BoardState = this->DuelState->GetBoardState();

	// Get available upcoming columns
	TArray<uint8> AvailableColumns;
	for (uint8 Column = 0; Column < BoardState->GetColumnCount(); Column++)
	{
		if (BoardState->GetUpcomingCardAt(Column) == NULL)
		{
			AvailableColumns.Add(Column);
		}
	}
	if (AvailableColumns.Num() == 0)
	{
		return -1;
	}

	// Get empty columns (columns without minions)
	TArray<uint8> EmptyColumns;
	for (uint8 i = 0; i < AvailableColumns.Num(); i++)
	{
		if (BoardState->GetCardAt(TEnumAsByte(Enemy), AvailableColumns[i]) == NULL)
		{
			EmptyColumns.Add(AvailableColumns[i]);
		}
	}
	if (EmptyColumns.Num() == 0)
	{
		return AvailableColumns[FMath::RandRange(0, AvailableColumns.Num() - 1)];
	}

	// Get prefferable columns (columns without enemy minions & opposing friendly minion)
	TArray<uint8> PrefferableColumns;
	for (uint8 i = 0; i < EmptyColumns.Num(); i++)
	{
		if (BoardState->GetCardAt(TEnumAsByte(Friendly), EmptyColumns[i]) != NULL)
		{
			PrefferableColumns.Add(EmptyColumns[i]);
		}
	}
	if (PrefferableColumns.Num() == 0)
	{
		return EmptyColumns[FMath::RandRange(0, EmptyColumns.Num() - 1)];
	}

	// Select a random column
	return PrefferableColumns[FMath::RandRange(0, PrefferableColumns.Num() - 1)];
}

void UEnemyDuelCharacter::EndTurn()
{
	this->DuelState->SwitchPlayerTurn();
}
