// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidget.h"

#include "GamePhase/GamePhaseSubsystem.h"

void UScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->IsOverlayVisible = false;
	
	UGameInstance* GameInstance = this->GetWorld()->GetGameInstance();
	if (GameInstance)
	{
		UGamePhaseSubsystem* GamePhaseSubsystem = GameInstance->GetSubsystem<UGamePhaseSubsystem>();
		if (GamePhaseSubsystem)
		{
			GamePhaseSubsystem->SetScreenWidget(this);
			GamePhaseSubsystem->MapPhase();
		}
	}
}
