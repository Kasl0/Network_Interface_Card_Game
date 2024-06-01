// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/MinionModifier.h"

UMinionModifier::UMinionModifier(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

UMinionModifier::UMinionModifier(uint32 Attack, int32 Health, UEffect* Effect, int32 Turns)
{
	this->AttackModifier = Attack;
	this->HealthModifier = Health;
	this->Effect = Effect;
	this->Effect->AddToRoot();
	this->TurnsLeft = Turns;
}
