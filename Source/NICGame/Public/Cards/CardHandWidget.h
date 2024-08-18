#pragma once

#include "CoreMinimal.h"
#include "Cards/CardHand.h"
#include "CardWidget.h"
#include "Blueprint/UserWidget.h"
#include "CardHandWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardHandWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CreateCardWidget(UCardData* CardData);
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveCard(UCardWidget* CardWidget);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveCardByCardData(UCardData* CardData);

	UFUNCTION(BlueprintCallable)
	void OnCardHandAdded(UCardData* CardData);

	UFUNCTION(BlueprintCallable)
	void OnCardHandRemoved(UCardData* CardData);
};
