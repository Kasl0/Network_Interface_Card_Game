// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cards/CardTypes/CardData.h"
#include "CreateCardChoice.generated.h"


/**
 * Helper class that creates ChooseCard Widget and handles the choice
 */
UCLASS()
class NICGAME_API UCreateCardChoice : public UObject
{

	GENERATED_BODY()

	UCreateCardChoice();

	// Do something with chosen card, e.g. add to deck
	TFunction<void(UCardData*)> CardChosenCallback;

	UClass* WidgetClass;

public:
	
	void CreateChoice(TArray<UCardData*> CardArray, TFunction<void(UCardData*)> CallbackFunction, UWorld* World);

	UFUNCTION(BlueprintCallable)
	void ChoiceMade(UCardData* Card);

};
