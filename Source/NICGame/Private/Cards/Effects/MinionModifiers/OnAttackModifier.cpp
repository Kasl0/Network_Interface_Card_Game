// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/OnAttackModifier.h"
#include "Cards/Effects/ChooseOneEffect.h"


void UOnAttackModifier::Init(UEffect* Effect)
{
	Super::Init();

	this->EffectAfterAttack = Effect;
	if (Cast<UChooseOneEffect>(Effect)) this->TakesCallback = true;
	this->Type = AfterAttack;
}

void UOnAttackModifier::ApplyEffect(UObject* EffectTarget, TFunction<void()> Callback)
{
	if (Callback != NULL)
	{
		UChooseOneEffect* ChooseOne = Cast<UChooseOneEffect>(EffectAfterAttack);
		ChooseOne->Apply(EffectTarget, Callback);
	}
	else
	{
		this->EffectAfterAttack->Apply(EffectTarget);
	}
}
