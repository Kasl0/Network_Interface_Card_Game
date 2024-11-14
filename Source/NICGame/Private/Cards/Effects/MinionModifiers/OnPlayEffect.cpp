// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/OnPlayEffect.h"

void UOnPlayEffect::Init(UEffect* OnPlayEffect)
{
	this->Effect = OnPlayEffect;
	this->Effect->AddToRoot();
}

void UOnPlayEffect::Apply(UObject* EffectTarget)
{
	this->Effect->Apply(EffectTarget);
}
