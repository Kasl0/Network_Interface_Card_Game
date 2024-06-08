// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardTypes/Minion.h"
//#include "Damageable.h"

void UMinion::CheckDeath()
{
	// TODO
	//  Check for death, handle death if health is 0
}

void UMinion::Init(uint8 Cost, std::string Name, std::string Description, int32 Attack, int32 Health)
{
	this->CardCost = Cost;
	this->CardName = FText::FromString(UTF8_TO_TCHAR(Name.c_str()));
	this->CardDescription = FText::FromString(UTF8_TO_TCHAR(Description.c_str()));
	this->BaseAttack = Attack;
	this->BaseHealth = Health;
	this->CurrentHealth = this->BaseHealth;
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
