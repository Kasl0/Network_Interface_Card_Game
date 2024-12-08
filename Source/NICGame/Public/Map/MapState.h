// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Map/MapNode.h"
#include "Map/MapLevel.h"
#include "MapState.generated.h"


/**
 * 
 */
UCLASS()
class NICGAME_API UMapState : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	// Temporary variable that dictates if mock map should be created
	bool IsMockMapCreated = false;
public:
	// Temporary function to create a placeholder map
	UFUNCTION(BlueprintCallable)
	void CreateMockMap();

	UPROPERTY(BlueprintReadOnly)
	TArray<FMapLevel> Map;

	UPROPERTY(BlueprintReadWrite)
	UMapNodeWidget* CurrentNode;

	UFUNCTION()
	void HandleNextNode(UMapNodeWidget* Node);
};
