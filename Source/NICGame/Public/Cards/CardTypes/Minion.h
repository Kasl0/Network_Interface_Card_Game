#pragma once

#include "CoreMinimal.h"
#include "Duel/Damageable.h"
#include "Cards/Effects/MinionModifier.h"
#include "Cards/CardTypes/CardData.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API UMinion : public UCardData, public IDamageable
{
	GENERATED_BODY()

	// Potentially temporary way to apply buffs or other modifiers
	TArray<UMinionModifier*> MinionModifiers;

	void CheckDeath();
	
public:	
	UPROPERTY(BlueprintReadOnly)
	int32 BaseAttack;

	UPROPERTY(BlueprintReadOnly)
	int32 BaseHealth;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealth;

	void Init(uint8 Cost, std::string Name, std::string Description, int32 Attack, int32 Health);

	// Get Attack value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetAttack();

	// Get current Health value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	void AttackTarget(TScriptInterface<IDamageable> Target);

	virtual void TakeDamage(int32 DamageValue, UObject* Source) override;

	void AddMinionModifier(UMinionModifier* Modifier);
};
