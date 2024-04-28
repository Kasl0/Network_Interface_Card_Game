// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardData : public UObject
{
	GENERATED_BODY()

public:
	void SetData(std::string Name, std::string Description);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardDescription;
};
