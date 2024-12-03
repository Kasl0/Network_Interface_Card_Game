#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CardService.generated.h"
#include "Cards/CardTypes/Minion.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UCardService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCardData* GetCardData(int32 id);
	UCardData* GetRandomEnemyCard(int8 layer); // layer value of -1 means random card from all layers
	TArray<UMinion*> ParseSummonMinion(TSharedPtr<FJsonObject> args);

protected:
	void InitialiseCardServiceIfNotInitialised();
	UCardData* GetCardDataFromJson(TSharedPtr<FJsonObject> CardObject);
	FString GetStringValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	int32 GetIntValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	bool GetBoolValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	TSharedPtr<FJsonObject> GetNestedObject(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	UMinion* GetMinionFromJson(int32 Mana, FString Name, FString GameDescription, FString IrlDescription, FString ImageFilename, int32 layer, TSharedPtr<FJsonObject> args);
	UEffect* ParseEffect(TSharedPtr<FJsonObject> EffectObject);

	TArray<TSharedPtr<FJsonValue>> JsonArray;
};
