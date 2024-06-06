// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UBoardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere)
	uint8 ColumnCount;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* UpcomingRow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Battlefield;

public:
	UFUNCTION(BlueprintCallable)
	uint8 GetColumnCount() const { return ColumnCount; }

	UFUNCTION(BlueprintCallable)
	UCardWidget* GetUpcomingCardWidgetAt(uint8 Column);

	UFUNCTION(BlueprintCallable)
	void SetUpcomingCardWidgetAt(uint8 Column, class UCardWidget* CardWidget);

	UFUNCTION(BlueprintCallable)
	void MoveUpcomingCardsToBattlefield();


	UFUNCTION(BlueprintCallable)
	UCardWidget* GetCardWidgetAt(uint8 Row, uint8 Column);

	UFUNCTION(BlueprintCallable)
	void SetCardWidgetAt(uint8 Row, uint8 Column, class UCardWidget* CardWidget);
};
