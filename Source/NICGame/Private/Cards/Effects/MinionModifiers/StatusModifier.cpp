// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/StatusModifier.h"
#include "Cards/Effects/MinionModifiers/EModifierType.h"

void UStatusModifier::Init(bool Poison, bool Taunt)
{
	Super::Init();
	
	this->SetPoison(Poison);
	this->SetTaunt(Taunt);
	this->Type = TEnumAsByte<EModifierType>(Status);
}

void UStatusModifier::SetPoison(bool Poison)
{
	this->applyPoison = Poison;
}

void UStatusModifier::SetTaunt(bool Taunt)
{
	this->applyTaunt = Taunt;
}
