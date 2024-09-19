// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapState.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly)
	UMapState* MapState;

	UFUNCTION(BlueprintImplementableEvent)
	void DrawMap();
};
