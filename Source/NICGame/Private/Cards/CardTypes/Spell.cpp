// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardTypes/Spell.h"

void USpell::Init(UEffect* Effect)
{
	this->SpellEffect = Effect;
	this->SpellEffect->AddToRoot();
}

void USpell::Apply(UObject* SpellTarget)
{
	this->SpellEffect->Apply(SpellTarget);
}
