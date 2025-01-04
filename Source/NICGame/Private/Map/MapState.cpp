// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapState.h"
#include "GamePhase/GamePhaseSubsystem.h"

void UMapState::CreateMockMap()
{
	if (IsMockMapCreated) return;

	UMapNodeWidget* Start = NewObject<UMapNodeWidget>();
	Start->Init(EMapNodeType::EnemyNode, 0);
	UMapNodeWidget* Enemy1 = NewObject<UMapNodeWidget>();
	Enemy1->Init(EMapNodeType::EnemyNode, 1);
	UMapNodeWidget* Enemy2 = NewObject<UMapNodeWidget>();
	Enemy2->Init(EMapNodeType::EnemyNode, 2);
	UMapNodeWidget* Boss = NewObject<UMapNodeWidget>();
	Boss->Init(EMapNodeType::BossNode, 3);

	UMapNodeWidget* Encounter1 = NewObject<UMapNodeWidget>();
	Encounter1->Init(EMapNodeType::UnknownNode, 1);
	UMapNodeWidget* Encounter2 = NewObject<UMapNodeWidget>();
	Encounter2->Init(EMapNodeType::UnknownNode, 2);

	Start->AddNextNode(Enemy1);
	Start->AddNextNode(Encounter1);
	Enemy1->AddNextNode(Encounter2);
	Enemy1->AddNextNode(Enemy2);
	Encounter1->AddNextNode(Enemy2);
	Enemy2->AddNextNode(Boss);
	Encounter2->AddNextNode(Boss);

	FMapLevel L1;
	FMapLevel L2;
	FMapLevel L3;
	FMapLevel L4;
	this->Map.Add(L1);
	this->Map.Add(L2);
	this->Map.Add(L3);
	this->Map.Add(L4);

	this->Map[0].Add(Start);
	this->Map[1].Add(Enemy1);
	this->Map[1].Add(Encounter1);
	this->Map[2].Add(Encounter2);
	this->Map[2].Add(Enemy2);
	this->Map[3].Add(Boss);

	this->IsMockMapCreated = true;

	this->CurrentNode = nullptr;
}

void UMapState::HandleNextNode(UMapNodeWidget* Node)
{
	this->CurrentNode = Node;

	UGameInstance* Instance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UGamePhaseSubsystem* GamePhase = Cast<UGamePhaseSubsystem>(Instance->GetSubsystem<UGamePhaseSubsystem>());
	if (Node->NodeType == TEnumAsByte<EMapNodeType>(EnemyNode) || Node->NodeType == TEnumAsByte<EMapNodeType>(BossNode))
	{
		GamePhase->DuelPhase();
	}
	else if (Node->NodeType == TEnumAsByte<EMapNodeType>(EMapNodeType::UnknownNode))
	{
		GamePhase->EncounterPhase();
	}
}
