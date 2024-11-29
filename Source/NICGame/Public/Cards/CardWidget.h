// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CardWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Background;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CardName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CardGameDescription;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CardImage;

public:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UCardData* CardData;
};
