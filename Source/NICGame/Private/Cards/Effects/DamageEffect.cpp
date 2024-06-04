// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/DamageEffect.h"

#include "Damageable.h"
#include "Cards/CardData.h"

void UDamageEffect::Init(uint32 Value)
{
	this->DamageValue = Value;
}

void UDamageEffect::Apply(UObject* EffectTarget)
{
	IDamageable* Damageable = Cast<IDamageable>(EffectTarget);
	if (Damageable != nullptr)
	{
		Damageable->TakeDamage(this->DamageValue, this);
	}
}
