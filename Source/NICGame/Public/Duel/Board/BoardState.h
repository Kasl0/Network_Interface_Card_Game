#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Duel/EBoardSide.h"
#include "Cards/CardTypes/CardData.h"
#include "BoardState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBoardStateDelegate);

/**
 * Handles Board logic
 */
UCLASS()
class NICGAME_API UBoardState : public UObject
{
	GENERATED_BODY()

public:
	
	/*
	* Constructor
	*/
	UBoardState();

	/*
	* Event that is broadcasted when the board changes
	*/
	FBoardStateDelegate OnBoardChanged;

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
	* Get the number of columns on the board
	* @return The number of columns on the board
	*/
	uint8 GetColumnCount() const { return this->ColumnCount; }

private:
	UPROPERTY()
	uint8 ColumnCount;

	UPROPERTY()
	TArray<UCardData*> UpcomingRow;

	UPROPERTY()
	TArray<UCardData*> Board;

	UFUNCTION()
	void BroadcastBoardChanged();
};
