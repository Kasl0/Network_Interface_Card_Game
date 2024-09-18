// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapNode.h"
#include <GamePhase/GamePhaseSubsystem.h>
#include <Map/MapState.h>

void UMapNodeWidget::Init(EMapNodeType Type, int32 Level)
{
	this->NodeType = Type;
	this->NodeLevel = Level;
}

void UMapNodeWidget::AddNextNode(UMapNodeWidget* Next)
{	
	this->NextNodes.Add(Next);
}

void UMapNodeWidget::NodeChosen(UMapNodeWidget* Node)
{
	UGameInstance* Game = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (Game)
	{
		UMapState* MapState = Cast<UMapState>(Game->GetSubsystem<UMapState>());
		MapState->CurrentNode = Node;

		UGamePhaseSubsystem* GamePhase = Cast<UGamePhaseSubsystem>(Game->GetSubsystem<UGamePhaseSubsystem>());
		GamePhase->DuelPhase();
	}
}
