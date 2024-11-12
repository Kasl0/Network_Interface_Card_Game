// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TaxonomySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UTaxonomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	// Y Axis for Bartle taxonomy
	UPROPERTY()
	int32 ActingAxis = 0;

	// X Axis for Bartle taxonomy
	UPROPERTY()
	int32 PlayersVsWorldAxis = 0;

public:
	// Change positive for World, negative for Players
	UFUNCTION(BlueprintCallable)
	void ChangeXAxisValue(int32 Change);

	// Change positive for Acting, negative for Interacting
	UFUNCTION(BlueprintCallable)
	void ChangeYAxisValue(int32 Change);

	// Only for initialization
	UFUNCTION(BlueprintCallable)
	void SetXAxisValue(int32 Change);

	// Only for initialization
	UFUNCTION(BlueprintCallable)
	void SetYAxisValue(int32 Change);
};