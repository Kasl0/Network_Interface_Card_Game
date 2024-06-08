// Fill out your copyright notice in the Description page of Project Settings.


#include "Duel/DuelCharacter.h"

void UDuelCharacter::Init()
{
	this->BaseHealth = 15;
	this->CurrentHealth = this->BaseHealth;
}

void UDuelCharacter::TakeDamage(int32 DamageValue, UObject* Source)
{
	this->CurrentHealth -= DamageValue;
	// TODO
	//  Check and handle death
}
