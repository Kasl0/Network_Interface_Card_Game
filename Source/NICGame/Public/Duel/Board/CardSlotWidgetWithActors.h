#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardActor.h"
#include "Components/Overlay.h"
#include "CardSlotWidgetWithActors.generated.h"

/**
 *
 */
UCLASS()
class NICGAME_API UCardSlotWidgetWithActors : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* Overlay;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool IsOccupied();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	ACardActor* GetCard();
};
