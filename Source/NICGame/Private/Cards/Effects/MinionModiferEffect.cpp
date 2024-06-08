// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModiferEffect.h"

#include "Cards/CardTypes/Minion.h"

void UMinionModiferEffect::Init(UMinionModifier* MinionModifier)
{
	this->Modifier = MinionModifier;
	this->Modifier->AddToRoot();
}

void UMinionModiferEffect::Apply(UObject* EffectTarget)
{
	UMinion* Minion = Cast<UMinion>(EffectTarget);
	if (Minion)
	{
		Minion->AddMinionModifier(this->Modifier);
	}
}
