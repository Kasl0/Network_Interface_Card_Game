// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ScreenWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UScreenWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RenderInWorld();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RenderOnScreen();
};
