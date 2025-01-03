﻿#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "Cards/Effects/Effect.h"
#include "Duel/EBoardSide.h"
#include "Spell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API USpell : public UCardData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	UEffect* SpellEffect;

	void Init(UEffect* Effect);

	bool IsPlayable(EBoardSide Side) override;

	UFUNCTION(BlueprintCallable)
	void Apply(UObject* SpellTarget);
};
