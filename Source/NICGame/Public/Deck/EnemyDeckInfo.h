#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemyDeckInfo.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UEnemyDeckInfo : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCardData* GetCard();
};
