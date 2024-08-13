#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cards/CardWidget.h"
#include "Components/Overlay.h"
#include "CardSlotWidget.generated.h"

/**
 *
 */
UCLASS()
class NICGAME_API UCardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* Overlay;

public:
	UFUNCTION(BlueprintCallable)
	bool IsOccupied();

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetCardWidget();
};
