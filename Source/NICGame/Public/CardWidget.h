// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CardWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UCardData* CardData;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Background;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CardName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CardDescription;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CardImage;

	UFUNCTION()
	void SetName(FText Name) const;
	UFUNCTION()
	void SetDescription(FText Description) const;
};
