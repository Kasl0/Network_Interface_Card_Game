#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardActor.h"
#include "Duel/Board/CardSlotWidgetWithActors.h"
#include "UpcomingCardSlotWidgetWithActors.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UUpcomingCardSlotWidgetWithActors : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardSlotWidgetWithActors* CardSlot;

public:
	UFUNCTION()
	bool IsOccupied();

	UFUNCTION(BlueprintCallable)
	ACardActor* GetCard();
};
