// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomEncounter.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API URandomEncounter : public UObject
{
	GENERATED_BODY()
	
	static TArray<int32> EncounterIds;

	int32 GetRandomEncounterId();

	int32 CurrentEncounterId = -1;

	UPROPERTY()
	UWorld* WorldPointer;

public:
	void CreateRandomEncounter(UWorld* World);

	UFUNCTION()
	void AfterEncounter();
};
