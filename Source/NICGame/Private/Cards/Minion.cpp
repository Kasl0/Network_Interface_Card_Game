// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Minion.h"

void UMinion::SetData(uint8 Cost, std::string Name, std::string Description, int32 Attack, int32 Health)
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
	return this->BaseAttack;
}

int32 UMinion::GetCurrentHealth()
{
	return this->CurrentHealth;
}

void UMinion::TakeDamage(int32 DamageValue)
{
	this->CurrentHealth -= DamageValue;

	// TODO
	//  Check for death etc.
}
