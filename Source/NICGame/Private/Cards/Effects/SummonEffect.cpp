// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/SummonEffect.h"
#include "Cards/CardService.h"
#include "Duel/DuelState.h"

void USummonEffect::SummonMinion(UMinion* Minion, UBoardState* BoardState, EBoardSide Side)
{
	for (int32 i = 0; i < BoardState->GetColumnCount(); i++)
	{
		if (BoardState->GetCardAt(Side, i) == NULL)
		{
			BoardState->PlaceCard(Minion, Side, i);
			return;
		}
	}
}

void USummonEffect::Init(TSharedPtr<FJsonObject> args, UWorld* Wrld)
{
	this->MinionsToSummonArgs = args;
	this->World = Wrld;
}

void USummonEffect::ApplySummonEffect(EBoardSide Side)
{
	UGameInstance* Ins = Cast<UGameInstance>(World->GetGameInstance());
	CardService* Service = Cast<CardService>(Ins->GetSubsystem<CardService>());
	UDuelState* DuelState = Cast<UDuelState>(Ins->GetSubsystem<UDuelState>());
	
	TArray<UMinion*> Minions = Service->ParseSummonMinion(MinionsToSummonArgs);

	for (auto Minion : Minions)
	{
		this->SummonMinion(Minion, DuelState->GetBoardState(), Side);
	}
}
