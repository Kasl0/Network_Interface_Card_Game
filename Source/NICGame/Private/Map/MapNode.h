// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/EMapNodeType.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "MapNode.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UMapNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Init(EMapNodeType Type, int32 Level);
	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TEnumAsByte<EMapNodeType> NodeType;

	// Tells which node in order this one is (e.g. starting node is 0, next is 1 etc.)
	UPROPERTY(BlueprintReadWrite)
	int32 NodeLevel;

	// Children nodes
	UPROPERTY(BlueprintReadOnly)
	TArray<UMapNodeWidget*> NextNodes;

	UFUNCTION()
	void AddNextNode(UMapNodeWidget* Next);

	// Called when node is clicked on the map, changes the Game Phase to corresponding to node type (for now simply starts a fight)
	UFUNCTION(BlueprintCallable)
	void NodeChosen(UMapNodeWidget* Node);
};
