// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleDeck.h"
#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHandWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCardData*> CardDataArray;
	
	UPROPERTY(BlueprintReadWrite)
	UBattleDeck* BattleDeck;
	
public:
	void DrawCard();
};
