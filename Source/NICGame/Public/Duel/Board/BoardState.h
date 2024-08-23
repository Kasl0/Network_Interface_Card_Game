#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "Duel/EBoardSide.h"
#include "BoardState.generated.h"

class UDuelState;
class UCardData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBoardStateDelegate);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FMinionAttackDelegate, int32, MinionIndex, int32, MinionSide);

/**
 * Handles Board logic
 */
UCLASS()
class NICGAME_API UBoardState : public UObject
{
	GENERATED_BODY()

	/*
	* Function to call after Minion Attack is complete
	* Continues turn switch logic
	*/
	TFunction<void(EBoardSide EndingTurn)> AfterMinionAttack;

	/*
	* Helper variables to use during minion attack
	*/
	EBoardSide CurrentAttackerSide;
	int CurrentlyAttackingMinion;

public:

	/*
	* Event that is broadcasted when the board changes
	*/
	FBoardStateDelegate OnMinionMove;
	FBoardStateDelegate OnBoardChanged;
	FMinionAttackDelegate OnMinionAttack;

	/*
	* Initialize the board with the specified number of columns
	* @param State The duel state that the board is associated with
	* @param ColumnCnt The number of columns to initialize the board with
	* @param World Object returned by GetWorld
	*/
	void Init(UDuelState* State, uint8 ColumnCnt, UWorld* World);

	/*
	* Get the card at the specified position in the upcoming row
	* @param Column The column to get the card from
	* @return The card at the specified position, or NULL if there is no card
	*/
	UCardData* GetUpcomingCardAt(uint8 Column);

	/*
	* Get the card at the specified position
	* @param Side The side to get the card from
	* @param Column The column to get the card from
	* @return The card at the specified position, or NULL if there is no card
	*/
	UFUNCTION(BlueprintCallable)
	UCardData* GetCardAt(EBoardSide Side, uint8 Column);

	/*
	* Place the upcoming card in the specified column
	* @param Card The card to place
	* @param Column The column to place the card in
	* @return True if the card was placed, false otherwise
	*/
	bool PlaceUpcomingCard(UCardData* Card, uint8 Column);

	/*
	* Place the card in the specified column and side
	* @param Card The card to place
	* @param Side The side to place the card on
	* @param Column The column to place the card in
	* @return True if the card was placed, false otherwise
	*/
	bool PlaceCard(UCardData* Card, EBoardSide Side, uint8 Column);

	/*
	* Move the upcoming cards to the battlefield
	*/
	void MoveUpcomingCardsToBattlefield();

	/*
	* Attack the minions on the opposite side
	* @param AttackerSide The side that is attacking
	*/
	void MinionAttack(EBoardSide AttackerSide, TFunction<void(EBoardSide EndingTurn)> OnMinionAttackComplete);

	/*
	* Attack with minion in a specific column (in a separate column to set intervals between attacks).
	* Recursively calls next column after a delay
	*/
	void MinionAttackInColumn();

	/*
	* Destroy the card
	* @param Card The card to destroy
	*/
	void DestroyCard(UCardData* Card);

	/*
	* Get the number of columns on the board
	* @return The number of columns on the board
	*/
	uint8 GetColumnCount();

	/*
	* Check if the board side is full
	* @param Side The side to check
	* @return True if the board side is full, false otherwise
	*/
	bool IsBoardSideFull(EBoardSide Side);

	/*
	* Check if the board side is empty
	* @param Side The side to check
	* @return True if the board side is empty, false otherwise
	*/
	bool IsBoardSideEmpty(EBoardSide Side);

private:
	UPROPERTY()
	class UDuelState* DuelState;

	UPROPERTY()
	uint8 ColumnCount;

	UWorld* CurrentWorld;

	UPROPERTY()
	TArray<UCardData*> UpcomingRow;

	UPROPERTY()
	TArray<UCardData*> Board;

	UFUNCTION()
	void BroadcastBoardChanged();
};
