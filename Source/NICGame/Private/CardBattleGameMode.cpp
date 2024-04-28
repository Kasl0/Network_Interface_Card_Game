// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBattleGameMode.h"
#include "CardBattleCharacter.h"

ACardBattleGameMode::ACardBattleGameMode()
{
	DefaultPawnClass = ACardBattleCharacter::StaticClass();
}
