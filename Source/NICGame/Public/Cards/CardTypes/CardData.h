#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Duel/EBoardSide.h"
#include "Components/Image.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardData : public UObject
{
	GENERATED_BODY()

public:
	virtual void SetData(uint8 Cost, std::string Name, std::string Description, FString ImageFilename);

	void SetCardImage(FString ImageFilename);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 CardCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CardDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush CardBrush;

	UFUNCTION(BlueprintCallable)
	virtual bool IsPlayable(EBoardSide Side);
};
