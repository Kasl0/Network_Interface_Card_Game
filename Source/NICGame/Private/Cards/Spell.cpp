// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Spell.h"

void USpell::init(UEffect* Effect)
{
	this->SpellEffect = Effect;
	this->SpellEffect->AddToRoot();
}

void USpell::Apply(UObject* SpellTarget)
{
	this->SpellEffect->Apply(SpellTarget);
}
