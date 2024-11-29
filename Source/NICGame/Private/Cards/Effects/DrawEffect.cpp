// Fill out your copyright notice in the Description page of Project Settings.

#include "Cards/Effects/DrawEffect.h"
#include "Duel/FriendlyDuelCharacter.h"

void UDrawEffect::Init(uint32 Value)
{
	this->CardsToDraw = Value;
}

void UDrawEffect::Apply(UObject* EffectTarget)
{
	UFriendlyDuelCharacter* Character = Cast<UFriendlyDuelCharacter>(EffectTarget);
	if (Character != nullptr)
	{
		for (int32 i = 0; i < CardsToDraw; i++)
		{
			Character->DrawCard();
		}
	}
}
