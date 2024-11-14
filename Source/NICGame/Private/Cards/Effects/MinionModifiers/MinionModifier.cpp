﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/MinionModifier.h"

#include "Cards/CardTypes/Minion.h"

void UMinionModifier::Apply(UObject* EffectTarget)
{
	UMinion* Minion = Cast<UMinion>(EffectTarget);
	if (Minion)
	{
		Minion->AddMinionModifier(this);
	}
}
