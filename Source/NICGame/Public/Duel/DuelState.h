// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DuelCharacter.h"
#include "Cards/CardWidget.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DuelState.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDuelState : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	// Selected card
	UPROPERTY(EditAnywhere, Category = "Card")
	UCardWidget* SelectedCard = nullptr;

public:
	// Initializes duel and necessary variables
	void StartDuel();
	
	// Enum used for current turn, board-wide effects etc.
	enum EBoardSide {Friendly = 0, Enemy = 1};
	
	// Get selected card
	UFUNCTION(BlueprintCallable)
	UCardWidget* GetSelectedCard() const;

	// Set selected card
	UFUNCTION(BlueprintCallable)
	void SetSelectedCard(UCardWidget* NewSelectedCard);

	// Handles turn change to opposite player
	UFUNCTION(BlueprintCallable)
	void SwitchTurn();
	
private:
	EBoardSide CurrentTurn;

	TMap<EBoardSide, UDuelCharacter*> DuelCharacters;
};
