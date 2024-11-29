// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/StatModifier.h"

void UStatModifier::Init(int32 Attack, int32 Health)
{
	Super::Init();

	this->AttackModifier = Attack;
	this->HealthModifier = Health;
	this->Type = Stat;
}
