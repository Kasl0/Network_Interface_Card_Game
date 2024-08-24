#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cards/CardWidget.h"
#include "UObject/NoExportTypes.h"
#include "Duel/Board/BoardState.h"
#include "Components/HorizontalBox.h"
#include "Components/UniformGridPanel.h"
#include "BoardWidget.generated.h"

/**
 * Handles visualising Board 
 */
UCLASS()
class NICGAME_API UBoardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	uint8 ColumnCount;

	UPROPERTY()
	UBoardState* BoardState;

	// Variable that dictates which column in upcoming row to move a minion from
	int32 ColumnToMoveMinionFrom;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* UpcomingRow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* Battlefield;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnMinionAttack(int32 MinionIndex, int32 MinionSide);

	UFUNCTION(BlueprintCallable)
	void OnMoveMinion();

	UFUNCTION(BlueprintCallable)
	void OnBoardReset();

	// Function called by timer, handles moving cards from upcoming to battlefield
	void MoveFromUpcomingRow();

	// Function called after all cards are moved to battlefield
	UFUNCTION(BlueprintCallable)
	void OnBattlefieldChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateUpcomingCardWidgetAt(uint8 Column, UCardData* CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveUpcomingCardWidgetAt(uint8 Column);

	UFUNCTION(BlueprintImplementableEvent)
	void MoveUpcomingCardToBoard(uint8 Column);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateCardWidgetAt(uint8 Row, uint8 Column, UCardData* CardData);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveCardWidgetAt(uint8 Row, uint8 Column);

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetUpcomingCardWidgetAt(uint8 Column);

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetCardWidgetAt(uint8 Row, uint8 Column);

	UFUNCTION(BlueprintCallable)
	uint8 GetColumnCount() const { return this->ColumnCount; }

	// Checks if all cards on the battlefield finished their animations
	UFUNCTION(BlueprintImplementableEvent)
	bool AreAnimationsFinished();
};
