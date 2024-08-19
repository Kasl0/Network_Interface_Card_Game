#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Cards/CardTypes/CardData.h"
#include "Deck/BattleDeck.h"
#include "CardHand.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardHandAddDelegate, UCardData*, CardWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardHandRemoveDelegate, UCardData*, CardWidget);

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHand : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<UCardData*> CardDataArray;

public:

	/*
	* Event for when a card is added to the hand
	*/
	FCardHandAddDelegate OnCardHandAdd;

	/*
	* Event for when a card is removed from the hand
	*/
	FCardHandRemoveDelegate OnCardHandRemove;

	/*
	* Draw a card from the deck
	*/
	UFUNCTION(BlueprintCallable)
	void DrawCard();

	/*
	* Get the card data at the specified index
	* @param Index The index of the card
	* @return The card data at the specified index
	*/
	UCardData* GetCardDataAt(uint8 Index);

	/*
	* Get the number of cards in the hand
	* @return The number of cards in the hand
	*/
	uint8 GetCardDataCount();

	/*
	* Add a card to the hand
	* @param CardData The card to add
	*/
	UFUNCTION(BlueprintCallable)
	void AddCardData(UCardData* CardData);

	/*
	* Remove a card from the hand
	* @param CardData The card to remove
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveCardData(UCardData* CardData);

	/*
	* Remove all cards from the hand
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllCardData();

private:
	UFUNCTION()
	void BroadcastCardHandAdded(UCardData* CardData);

	UFUNCTION()
	void BroadcastCardHandRemoved(UCardData* CardData);
};
