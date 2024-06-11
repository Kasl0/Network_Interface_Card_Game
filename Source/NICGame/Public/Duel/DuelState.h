// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DuelCharacter.h"
#include "Cards/CardWidget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Duel/EBoardSide.h"
#include "DuelState.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDuelState : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	//bool DuelInProgress = false;
	
	// Selected card
	UPROPERTY(EditAnywhere, Category = "Card")
	UCardWidget* SelectedCard = nullptr;

public:
	// Initializes duel and necessary variables
	void StartDuel();
	
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
	bool PlayCard(UCardData* CardData);
protected:
	EBoardSide CurrentTurn;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> DuelCharacters;
};
