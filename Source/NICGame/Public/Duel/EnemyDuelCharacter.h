#pragma once

#include "CoreMinimal.h"
#include "Duel/DuelCharacter.h"
#include "Duel/DuelState.h"
#include "Cards/CardTypes/Minion.h"
#include "EnemyDuelCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UEnemyDuelCharacter : public UDuelCharacter
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void StartTurn() override;

	UFUNCTION()
	void InitializeDuelState(UDuelState* State); // we can't get it from GetWorld()->GetGameInstance()->GetSubsystem<UDuelState>(); coz UEnemyDuelCharacter as a UObject doesn't have access to the world

private:

	UPROPERTY()
	UDuelState* DuelState;

	// Move upcoming cards
	UFUNCTION()
	void MoveCards();

	// After animations are finished, play new cards
	UFUNCTION()
	void PlayCards();

	UFUNCTION()
	uint8 GetPreferredEmptyColumn();
};
