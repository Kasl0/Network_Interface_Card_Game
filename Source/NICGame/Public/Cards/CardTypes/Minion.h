#pragma once

#include "CoreMinimal.h"
#include "Duel/Damageable.h"
#include "Cards/Effects/MinionModifiers/MinionModifier.h"
#include "Cards/CardTypes/CardData.h"
#include "Duel/EBoardSide.h"
#include "Cards/CardTypes/MinionFactionEnum.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API UMinion : public UCardData, public IDamageable
{
	GENERATED_BODY()

	void CheckDeath();
	
public:	
	// Potentially temporary way to apply buffs or other modifiers
	UPROPERTY(BlueprintReadOnly)
	TArray<UMinionModifier*> MinionModifiers;

	UPROPERTY(BlueprintReadOnly)
	int32 BaseAttack;

	UPROPERTY(BlueprintReadOnly)
	int32 BaseHealth;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealth;

	virtual void Init(uint8 Cost, std::string Name, std::string GameDescription, std::string IrlDescription, int32 Attack, int32 Health, FString Image, int32 Layer);

	bool IsPlayable(EBoardSide Side) override;

	// Get Attack value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetAttack();

	// Get current Health value with modifiers
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth();

	//UFUNCTION(BlueprintCallable)
	void AttackTarget(TScriptInterface<IDamageable> Target, TFunction<void()> Callback);

	bool ApplyAfterAttackModifiers(TFunction<void()> Callback);

	virtual void TakeDamage(int32 DamageValue, UObject* Source) override;

	void AddMinionModifier(UMinionModifier* Modifier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EMinionFaction> MinionFaction;

	bool HasTaunt = false;

	bool HasPoison = false;
};
