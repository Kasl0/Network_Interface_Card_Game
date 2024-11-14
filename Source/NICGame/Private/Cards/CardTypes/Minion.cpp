#include "Cards/CardTypes/Minion.h"
#include "Duel/DuelState.h"
#include "Cards/Effects/MinionModifiers/StatModifier.h"
#include "Cards/Effects/MinionModifiers/StatusModifier.h"
#include "Cards/Effects/MinionModifiers/EModifierType.h"
#include "Duel/Board/BoardState.h"
//#include "Damageable.h"

void UMinion::CheckDeath()
{
	if (this->CurrentHealth <= 0)
	{
		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
		DuelState->GetBoardState()->DestroyCard(this);
	}
}

void UMinion::Init(uint8 Cost, std::string Name, std::string GameDescription, std::string IrlDescription, int32 Attack, int32 Health, FString Image, int32 Layer)
{
	this->CardCost = Cost;
	this->CardName = FText::FromString(UTF8_TO_TCHAR(Name.c_str()));
	this->CardGameDescription = FText::FromString(UTF8_TO_TCHAR(GameDescription.c_str()));
	this->CardIrlDescription = FText::FromString(UTF8_TO_TCHAR(IrlDescription.c_str()));
	this->BaseAttack = Attack;
	this->BaseHealth = Health;
	this->CurrentHealth = this->BaseHealth;
	this->CardLayer = Layer;
	this->SetCardImage(Image);
}

bool UMinion::IsPlayable(EBoardSide Side)
{
	if (!Super::IsPlayable(Side))
	{
		return false;
	}
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	return !DuelState->GetBoardState()->IsBoardSideFull(Side);
}

int32 UMinion::GetAttack()
{
	int32 Attack = this->BaseAttack;
	for (int i = 0; i < this->MinionModifiers.Num(); ++i)
	{
		if (this->MinionModifiers[i]->Type == TEnumAsByte<EModifierType>(Stat))
		{
			UStatModifier* StatModifier = Cast<UStatModifier>(this->MinionModifiers[i]);
			Attack += StatModifier->AttackModifier;
		}
	}
	return Attack;
}

int32 UMinion::GetCurrentHealth()
{
	return this->CurrentHealth;
}

void UMinion::AttackTarget(TScriptInterface<IDamageable> Target)
{
	int32 Damage = this->GetAttack();
	Target->TakeDamage(Damage, this);
	// If the target was a minion, damage self as well
	UMinion* TargetMinion = Cast<UMinion>(Target.GetObject());
	if (TargetMinion)
	{
		this->TakeDamage(TargetMinion->GetAttack(), TargetMinion);
	}
}

void UMinion::TakeDamage(int32 DamageValue, UObject* Source)
{
	this->CurrentHealth -= DamageValue;

	UMinion* SourceMinion = Cast<UMinion>(Source);
	if (SourceMinion && SourceMinion->HasPoison && DamageValue > 0)
	{
		this->CurrentHealth = 0;
	}

	this->CheckDeath();
}

void UMinion::AddMinionModifier(UMinionModifier* Modifier)
{
	Modifier->AddToRoot();
	this->MinionModifiers.Add(Modifier);

	if (Modifier->Type == TEnumAsByte<EModifierType>(Stat))
	{
		UStatModifier* StatModifier = Cast<UStatModifier>(Modifier);
		this->BaseHealth += StatModifier->HealthModifier;
		this->CurrentHealth += StatModifier->HealthModifier;
	}
	else if (Modifier->Type == TEnumAsByte<EModifierType>(Status))
	{
		UStatusModifier* StatusModifier = Cast<UStatusModifier>(Modifier);
		this->HasTaunt = StatusModifier->applyTaunt;
		this->HasPoison = StatusModifier->applyPoison;
	}

	this->CheckDeath();
}
