// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePhase/GamePhaseSubsystem.h"

#include "Duel/DuelState.h"


void UGamePhaseSubsystem::DuelPhase()
{
	this->GamePhase = EGamePhase::Duel;
	
	this->ScreenWidget->ShowBoard();
	this->ChangeOverlay(3);
	
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UDuelState* DuelState = GameInstance->GetSubsystem<UDuelState>();
		if (DuelState)
		{
			DuelState->StartDuel(TEnumAsByte(EBoardSide::Enemy));
		}
	}
}

void UGamePhaseSubsystem::MapPhase()
{
	this->GamePhase = EGamePhase::Map;

	this->ScreenWidget->ShowMap();
	this->ChangeOverlay(3);
}

void UGamePhaseSubsystem::ChangeOverlay(int32 Change)
{
	if (this->ScreenWidget)
	{
		this->ScreenWidget->ChangeOverlay(GamePhase,Change);
	}
}

void UGamePhaseSubsystem::SetScreenWidget(UScreenWidget* Screen)
{
	this->ScreenWidget = Screen;
}
