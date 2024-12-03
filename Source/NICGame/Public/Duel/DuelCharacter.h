#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "UObject/Object.h"
#include "Cards/CardHand.h"
#include "DuelCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDuelCharacter : public UObject, public IDamageable
{
	GENERATED_BODY()

	// Character starting health
	int32 BaseHealth;

protected:
	// Character health after damage, modifiers etc.
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealth;

	// Mana gained at the start of every turn
	UPROPERTY(BlueprintReadOnly)
	int32 BaseMana;

	// Mana left during this turn
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentMana;

	UPROPERTY()
	uint8 CardDrawInCurrentTurn;

public:
	virtual void StartTurn();

	void EndTurn();
	
	void Init(int32 Health = 30, int32 Mana = 0);
	
	virtual void TakeDamage(int32 DamageValue, UObject* Source) override;

	bool CheckDeath();

	int32 GetBaseMana() const;

	int32 GetCurrentMana() const;

	// Spend mana on cards, false if not enough mana
	bool UseMana(int32 Mana);
	
	int32 GetHealth();

	void IncrementCardDrawInCurrentTurn();

	UFUNCTION(BlueprintCallable)
	uint8 GetCardDrawInCurrentTurn();
};
