#pragma once

#include "CoreMinimal.h"
#include "Cards/CardTypes/CardData.h"


/**
 * 
 */
class NICGAME_API CardService : public UGameInstanceSubsystem
{
public:
	UCardData* GetCardData(int32 id);
	UCardData* GetRandomEnemyCard(int8 layer); // layer value of -1 means random card from all layers

protected:
	void InitialiseCardServiceIfNotInitialised();
	UCardData* GetCardDataFromJson(TSharedPtr<FJsonObject> CardObject);
	FString GetStringValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	int32 GetIntValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);
	bool GetBoolValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed);

	TArray<TSharedPtr<FJsonValue>> JsonArray;
};
