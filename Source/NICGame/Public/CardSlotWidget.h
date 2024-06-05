// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UCardWidget* CardWidget;

public:
	UFUNCTION(BlueprintCallable)
	bool IsOccupied();

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetCardWidget();

	UFUNCTION(BlueprintCallable)
	void SetCardWidget(class UCardWidget* NewCardWidget);

	UFUNCTION(BlueprintCallable)
	void OnCardSlotClicked();
};
