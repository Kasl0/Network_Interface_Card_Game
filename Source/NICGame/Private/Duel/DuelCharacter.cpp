// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/DuelCharacter.h"

void UDuelCharacter::StartTurn()
{
	this->CurrentMana = this->BaseMana;
}

void UDuelCharacter::Init(int32 Health, int32 Mana)
{
	this->BaseHealth = Health;
	this->CurrentHealth = this->BaseHealth;
	this->BaseMana = Mana;
}

void UDuelCharacter::TakeDamage(int32 DamageValue, UObject* Source)
{
	this->CurrentHealth -= DamageValue;
	// TODO
	//  Check and handle death
}

int32 UDuelCharacter::GetBaseMana() const
{
	return this->BaseMana;
}

int32 UDuelCharacter::GetCurrentMana() const
{
	return this->CurrentMana;
}

bool UDuelCharacter::UseMana(int32 Mana)
{
	if (Mana > this->CurrentMana)
	{
		return false;
	}
	else
	{
		this->CurrentMana -= Mana;
		return true;
	}
}

int32 UDuelCharacter::GetHealth()
{
	return this->CurrentHealth;
}
