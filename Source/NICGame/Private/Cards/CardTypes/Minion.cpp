#include "Cards/CardTypes/Minion.h"
#include "Duel/DuelState.h"
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
		Attack += this->MinionModifiers[i]->AttackModifier;
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
}

void UMinion::TakeDamage(int32 DamageValue, UObject* Source)
{
	this->CurrentHealth -= DamageValue;
	this->CheckDeath();
}

void UMinion::AddMinionModifier(UMinionModifier* Modifier)
{
	Modifier->AddToRoot();
	this->MinionModifiers.Add(Modifier);

	this->BaseHealth += Modifier->HealthModifier;
	this->CurrentHealth += Modifier->HealthModifier;
	this->CheckDeath();
}
