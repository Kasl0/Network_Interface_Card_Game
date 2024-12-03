// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CreateCardChoice.h"
#include "ChooseCardBase.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UChooseCardBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	UCreateCardChoice* Creator;

	UPROPERTY(BlueprintReadOnly)
	TArray<UCardData*> CardDataArray;

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeChoice();
};
