// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapNode.h"
#include <GamePhase/GamePhaseSubsystem.h>

void UMapNodeWidget::Init(EMapNodeType Type, int32 Level)
{
	this->NodeType = Type;
	this->NodeLevel = Level;
}

void UMapNodeWidget::AddNextNode(UMapNodeWidget* Next)
{	
	this->NextNodes.Add(Next);
}

void UMapNodeWidget::NodeChosen()
{
	UGameInstance* Game = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (Game)
	{
		UGamePhaseSubsystem* GamePhase = Cast<UGamePhaseSubsystem>(Game->GetSubsystem<UGamePhaseSubsystem>());
		GamePhase->DuelPhase();
	}
}
