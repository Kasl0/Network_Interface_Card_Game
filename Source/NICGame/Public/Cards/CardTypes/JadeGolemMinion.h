// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/Minion.h"
#include "JadeGolemMinion.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UJadeGolemMinion : public UMinion
{
	GENERATED_BODY()
	
public:
	void Init(uint8 Cost, std::string Name, std::string GameDescription, std::string IrlDescription, int32 Attack, int32 Health, FString Image, int32 Layer) override;

	static int32 Stats;
};
