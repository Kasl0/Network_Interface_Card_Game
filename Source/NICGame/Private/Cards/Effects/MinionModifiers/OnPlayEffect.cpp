// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/MinionModifiers/OnPlayEffect.h"
#include "Cards/Effects/SummonEffect.h"
#include "Cards/Effects/ChooseOneEffect.h"

void UOnPlayEffect::Init(UEffect* OnPlayEffect)
{
	Super::Init();

	this->Effect = OnPlayEffect;
	this->Effect->AddToRoot();

	this->Type = OnPlay;
}

void UOnPlayEffect::Apply(UObject* EffectTarget)
{
	if (USummonEffect* SummonEffect = Cast<USummonEffect>(Effect))
	{
		SummonEffect->ApplySummonEffect(Friendly);
	}
	else if (UChooseOneEffect* ChooseEffect = Cast<UChooseOneEffect>(Effect))
	{
		ChooseEffect->Apply(EffectTarget, NULL);
	} 
	else
	{
		this->Effect->Apply(EffectTarget);
	}
}
