#include "Cards/CardTypes/Minion.h"
#include "Duel/DuelState.h"
#include "Cards/Effects/MinionModifiers/StatModifier.h"
#include "Cards/Effects/MinionModifiers/StatusModifier.h"
#include "Cards/Effects/MinionModifiers/EModifierType.h"
#include "Cards/Effects/MinionModifiers/OnAttackModifier.h"
#include "Duel/Board/BoardState.h"
#include "Cards/Effects/MinionModifiers/OnPlayEffect.h"
//#include "Damageable.h"

void UMinion::CheckDeath()
{
	if (this->CurrentHealth <= 0)
	{
		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
		DuelState->GetBoardState()->DestroyCard(this, false);
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

void UMinion::AttackTarget(TScriptInterface<IDamageable> Target, TFunction<void()> Callback)
{
	// Ensure the Callback is valid before using it
	if (!Callback)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Callback passed to AttackTarget"));
		return;
	}

	int32 Damage = this->GetAttack();
	Target->TakeDamage(Damage, this);

	// Use a local copy of the Callback to prevent potential invalidation
	auto LocalCallback = Callback;
	bool CallbackUsed = this->ApplyAfterAttackModifiers(LocalCallback);

	// If the target was a minion, damage self as well
	UMinion* TargetMinion = Cast<UMinion>(Target.GetObject());
	if (TargetMinion)
	{
		this->TakeDamage(TargetMinion->GetAttack(), TargetMinion);
	}

	if (!CallbackUsed)
	{
		LocalCallback();
	}
}

void UMinion::ApplyOnPlayModifiers()
{
	for (UMinionModifier* Modifier : this->MinionModifiers)
	{
		if (Modifier->Type == TEnumAsByte<EModifierType>(OnPlay))
		{
			UOnPlayEffect* NewModifier = Cast<UOnPlayEffect>(Modifier);
			NewModifier->Apply(this);
		}
	}
}

bool UMinion::ApplyAfterAttackModifiers(TFunction<void()> Callback)
{
	bool CallbackUsed = false;
	for (UMinionModifier* Modifier : this->MinionModifiers)
	{
		if (Modifier->Type == TEnumAsByte<EModifierType>(AfterAttack))
		{
			UOnAttackModifier* NewModifier = Cast<UOnAttackModifier>(Modifier);
			if (NewModifier->TakesCallback && !CallbackUsed)
			{
				CallbackUsed = true;
				NewModifier->ApplyEffect(this, Callback);
			}
			else 
			{
				Modifier->ApplyEffect(this);
			}
		}
	}
	return CallbackUsed;
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
		if (StatusModifier->applyTaunt && !this->HasTaunt) {
			this->HasTaunt = true;
			this->CardGameDescription = this->CardGameDescription.Join(FText::FromString("\n"), FText::FromString("Prowokacja"));
		}
		if (StatusModifier->applyPoison && !this->HasPoison) {
			this->HasPoison = true;
			this->CardGameDescription = this->CardGameDescription.Join(FText::FromString("\n"), FText::FromString("Trucizna"));
		}
	}

	this->CheckDeath();
}
