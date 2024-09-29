// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePhase/EGamePhase.h"
#include "Cards/CardHUDWidget.h"
#include "ScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	bool IsOverlayVisible;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowMap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowBoard();

	/**
	 * Change visibility of overlay corresponding to game phase (e.g. CardHUD for Duel).
	 * Would make more sense to put this in UGamePhaseSubsystem, but it's easier to do a Blueprint Event here.
	 * @param Change What to do with overlay: 0 - hide, 1 - show, 2 - toggle, 3 - if visible, change to match GamePhase
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeOverlay(EGamePhase GamePhase, int32 Change = 2);

	UPROPERTY(BlueprintReadWrite)
	UCardHUDWidget* CardHUDWidget;
};
