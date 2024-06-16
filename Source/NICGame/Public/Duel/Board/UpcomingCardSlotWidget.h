#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cards/CardWidget.h"
#include "Duel/Board/CardSlotWidget.h"
#include "UpcomingCardSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UUpcomingCardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardSlotWidget* CardSlot;

public:
	UFUNCTION()
	bool IsOccupied();

	UFUNCTION()
	UCardWidget* GetCardWidget();
};
