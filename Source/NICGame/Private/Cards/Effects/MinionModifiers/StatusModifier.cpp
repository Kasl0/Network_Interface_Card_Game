// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/StatusModifier.h"

void UStatusModifier::Init(bool Poison, bool Taunt)
{
	this->SetPoison(Poison);
	this->SetTaunt(Taunt);
}

void UStatusModifier::SetPoison(bool Poison)
{
	this->applyPoison = Poison;
}

void UStatusModifier::SetTaunt(bool Taunt)
{
	this->applyTaunt = Taunt;
}
