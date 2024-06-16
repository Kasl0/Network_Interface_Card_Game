#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Duel/EBoardSide.h"
#include "Deck/EnemyDeckInfo.h"
#include "DuelState.generated.h"

// Forward declarations
class UCardWidget;
class UBoardState;
class UDuelCharacter;
class UCardData;

/**
 * 
 */
UCLASS()
class NICGAME_API UDuelState : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:
	UDuelState();

	//bool DuelInProgress = false;
	
	// Selected card
	UPROPERTY(EditAnywhere, Category = "Card")
	UCardWidget* SelectedCard = nullptr;

public:
	// Initializes duel and necessary variables
	void StartDuel(EBoardSide StartingSide);
	
	// Get selected card
	UFUNCTION(BlueprintCallable)
	UCardWidget* GetSelectedCard() const;

	// Set selected card
	UFUNCTION(BlueprintCallable)
	void SetSelectedCard(UCardWidget* NewSelectedCard);

	// Handles turn change to opposite player
	UFUNCTION(BlueprintCallable)
	void SwitchPlayerTurn();

	UFUNCTION(BlueprintCallable)
	TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> GetCharacters();

	// Add card to board, handle mana etc.
	UFUNCTION(BlueprintCallable)
	bool PlayCard(UCardData* CardData, uint8 Colum);

	// Get board state
	UFUNCTION(BlueprintCallable)
	UBoardState* GetBoardState();

	// Get enemy deck info
	UFUNCTION(BlueprintCallable)
	UEnemyDeckInfo* GetEnemyDeckInfo();

protected:
	EBoardSide CurrentTurn;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> DuelCharacters;

	UPROPERTY()
	UBoardState* BoardState;
};
