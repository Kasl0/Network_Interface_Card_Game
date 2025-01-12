// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidget.h"
#include "ScreenWidgetComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GamePhase/EGamePhase.h"
#include "GamePhaseSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UGamePhaseSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	
public:	
	UPROPERTY(BlueprintReadWrite)
	UScreenWidget* ScreenWidget;

	UPROPERTY(BlueprintReadWrite)
	UScreenWidgetComponent* ScreenWidgetComponent;

	// Switch to duel phase
	UFUNCTION(BlueprintCallable)
	void DuelPhase();

	UFUNCTION(BlueprintCallable)
	void EncounterPhase();

	// Switch to duel phase
	UFUNCTION(BlueprintCallable)
	void MapPhase();

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EGamePhase> GamePhase;

	// Helper function, calls UScreenWidget::ChangeOverlay, see for documentation
	UFUNCTION(BlueprintCallable)
	void ChangeOverlay(int32 Change);

	UFUNCTION(BlueprintCallable)
	void SetScreenWidget(UScreenWidget* Screen);
};
