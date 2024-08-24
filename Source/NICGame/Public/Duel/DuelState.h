#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Duel/EBoardSide.h"
#include "Deck/EnemyDeckInfo.h"
#include "DuelState.generated.h"

// Forward declarations
class UCardWidget;
class UBoardState;
class UBoardWidget;
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

	// Check if duel is in progress
	bool IsDuelInProgress();

	// Initializes duel and necessary variables
	void StartDuel(EBoardSide StartingSide);
	
	// Get selected card
	UFUNCTION(BlueprintCallable)
	UCardWidget* GetSelectedCard() const;

	// Set selected card
	UFUNCTION(BlueprintCallable)
	void SetSelectedCard(UCardWidget* NewSelectedCard);

	// Handles preparations for turn end (waiting for animations to finish)
	UFUNCTION()
	void PrepareTurnEnd();

	// Handles logic for ending a player's turn
	UFUNCTION(BlueprintCallable)
	void EndPlayerTurn();

	// Handles turn change to opposite player
	UFUNCTION(BlueprintCallable)
	void SwitchPlayerTurn(EBoardSide EndingTurn);

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

	UFUNCTION()
	void EndDuel(EBoardSide WiningSide, uint8 excessiveDamage);

	// Get current turn
	UFUNCTION(BlueprintCallable)
	EBoardSide GetCurrentTurn();

	// Get current turn duel character
	UFUNCTION(BlueprintCallable)
	UDuelCharacter* GetCurrentTurnCharacter();

	// Set Board Widget
	UFUNCTION()
	void SetBoardWidget(UBoardWidget* Widget);

	UPROPERTY()
	UBoardWidget* BoardWidget;

protected:
	EBoardSide CurrentTurn;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> DuelCharacters;

	UPROPERTY()
	UBoardState* BoardState;
};
