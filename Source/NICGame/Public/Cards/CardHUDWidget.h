// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void DrawCard();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* DrawCardButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCardHandWidget* CardHand;
};
