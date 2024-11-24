#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Duel/EBoardSide.h"
#include "Components/Image.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NICGAME_API UCardData : public UObject
{
	GENERATED_BODY()

public:
	virtual void SetData(uint8 Cost, std::string Name, std::string GameDescription, std::string IrlDescription, FString ImageFilename, int32 Layer);

	void SetCardImage(FString ImageFilename);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 CardCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardGameDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardIrlDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CardLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush CardBrush;

	UFUNCTION(BlueprintCallable)
	virtual bool IsPlayable(EBoardSide Side);
};
