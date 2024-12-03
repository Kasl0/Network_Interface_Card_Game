#include "Cards/CardService.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Cards/CardTypes/Minion.h"
#include "Cards/CardTypes/JadeGolemMinion.h"
#include "Cards/CardTypes/Spell.h"
#include "Cards/Effects/MinionModifiers/StatModifier.h"
#include "Cards/Effects/MinionModifiers/StatusModifier.h"
#include "Cards/Effects/MinionModifiers/OnAttackModifier.h"
#include "Cards/Effects/DrawEffect.h"
#include "Cards/Effects/SummonEffect.h"
#include "Cards/Effects/ShuffleIntoDeckEffect.h"
#include "Cards/Effects/ChooseOneEffect.h"
#include "Cards/Effects/MinionModifiers/OnPlayEffect.h"

/*
Json file structure:
[
	{
		"id": 1,
		"name": "Device name",
		"spellType": "Damage",
		"args": {
			// Arguments specific to the type of card, e.g. baseAttack and baseHealth for Minion
		},
		"manaCost": 1,
		"imageFilename": "image.png",
		"layer": 1,
		"isForUser": true,
		"gameDescription": "Card front page description - in game use if any",
		"irlDescription": "Card back page description - real life device description"
	},
	...
]
*/

void UCardService::InitialiseCardServiceIfNotInitialised()
{
	if (JsonArray.Num() > 0)
		return;
	FString JsonFilePath = FPaths::ProjectContentDir() + TEXT("Data/Cards/cardsData.json");
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		UE_LOG(LogTemp, Error, TEXT("Card Data deserialization failed."));
	}
}

UCardData* UCardService::GetCardData(int32 id)
{
	InitialiseCardServiceIfNotInitialised();
	for (TSharedPtr<FJsonValue> Value : JsonArray)
	{
		TSharedPtr<FJsonObject> CardObject = Value->AsObject();
		if (!CardObject.IsValid())
		{
			continue;
		}

		if (GetIntValue(CardObject, "id", true) == id)
		{
			return GetCardDataFromJson(CardObject);
		}
	}
	return nullptr;
}

UCardData* UCardService::GetRandomEnemyCard(int8 layer)
{
	InitialiseCardServiceIfNotInitialised();
	TArray<TSharedPtr<FJsonObject>> LayerCards;
	for (TSharedPtr<FJsonValue> Value : JsonArray)
	{
		TSharedPtr<FJsonObject> CardObject = Value->AsObject();
		if (!CardObject.IsValid())
		{
			continue;
		}

		if ((layer == -1 || GetIntValue(CardObject, "layer", false) == layer) && GetBoolValue(CardObject, "enemyCard", true))
		{
			LayerCards.Add(CardObject);
		}
	}

	if (LayerCards.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No cards found for layer %d"), layer);
		return nullptr;
	}

	int32 RandomIndex = FMath::RandRange(0, LayerCards.Num() - 1);
	return GetCardDataFromJson(LayerCards[RandomIndex]);
}

UCardData* UCardService::GetCardDataFromJson(TSharedPtr<FJsonObject> CardObject)
{
	int32 id = GetIntValue(CardObject, "id", true);
	FString name = GetStringValue(CardObject, "name", true);
	FString spellType = GetStringValue(CardObject, "spellType", false);
	int32 manaCost = GetIntValue(CardObject, "manaCost", true);
	TSharedPtr<FJsonObject> args = this->GetNestedObject(CardObject, "args", true);
	FString filename = GetStringValue(CardObject, "imageFilename", false);
	FString imageFilename;
	if (FPaths::FileExists(FPaths::ProjectContentDir() + TEXT("Data/Cards/Images/" + filename + ".png")))
	{
		imageFilename = TEXT("/Script/Engine.Texture2D'/Game/Data/Cards/Images/" + filename + '.' + filename + '\'');
	}
	else
	{
		imageFilename = TEXT("/Script/Engine.Texture2D'/Game/Data/Cards/ImageNotFound.ImageNotFound'");
	}
	int32 layer = GetIntValue(CardObject, "layer", false);
	FString gameDescription = GetStringValue(CardObject, "gameDescription", false);
	FString irlDescription = GetStringValue(CardObject, "irlDescription", false);

	if (spellType == "")
	{
		//int32 baseAttack = GetIntValue(args, "baseAttack", false);
		//int32 baseHealth = GetIntValue(args, "baseHealth", false);

		UMinion* Minion = GetMinionFromJson(manaCost, name, gameDescription, irlDescription, imageFilename, layer, args);
		return Minion;
	}
	else if (spellType == "MinionStat")
	{
		int32 baseAttack = GetIntValue(args, "attack", false);
		int32 baseHealth = GetIntValue(args, "health", false);

		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		UStatModifier* Modifier = NewObject<UStatModifier>();
		Modifier->Init(baseAttack, baseHealth);
		Spell->Init(Modifier);
		return Spell;
	}
	else if (spellType == "MinionStatus")
	{
		bool SetPoison = GetBoolValue(args, "poison", false);
		bool SetTaunt = GetBoolValue(args, "taunt", false);

		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		UStatusModifier* Modifier = NewObject<UStatusModifier>();
		Modifier->Init(SetPoison, SetTaunt);
		Spell->Init(Modifier);
		return Spell;
	}
	else if (spellType == "Draw")
	{
		int32 CardsToDraw = GetIntValue(args, "cards", false);
		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		UDrawEffect* Effect = NewObject<UDrawEffect>();
		Effect->Init(CardsToDraw);
		Spell->Init(Effect);
		return Spell;
	}
	else if (spellType == "Summon")
	{
		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		USummonEffect* Effect = NewObject<USummonEffect>();
		Effect->Init(args, GetWorld());
		Spell->Init(Effect);
		return Spell;
	}
	else if (spellType == "ShuffleIntoDeck")
	{
		int32 CardToShuffleId = GetIntValue(args, "id", true);
		int32 Count = GetIntValue(args, "count", true);

		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		UShuffleIntoDeckEffect* Effect = NewObject<UShuffleIntoDeckEffect>();
		Effect->Init(CardToShuffleId, Count, GetWorld());
		Spell->Init(Effect);
		return Spell;
	}
	else if (spellType == "chooseOne")
	{
		USpell* Spell = NewObject<USpell>();
		Spell->SetData(manaCost, TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*gameDescription), TCHAR_TO_UTF8(*irlDescription), imageFilename, layer);
		UEffect* Effect = ParseEffect(args);
		Spell->Init(Effect);
		return Spell;
	}
	// TODO: here handle other spell types
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spell type not implemented"));
		return nullptr;
	}
}

FString UCardService::GetStringValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed)
{
	FString FieldValue;
	if (CardObject->HasField(FieldName) && CardObject->TryGetStringField(FieldName, FieldValue))
	{
		return FieldValue;
	}
	else
	{
		if (nullNotAllowed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Field %s is null or not valid string"), *FieldName);
		}
		return "";
	}
}

int32 UCardService::GetIntValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed)
{
	int32 FieldValue;
	if (CardObject->HasField(FieldName) && CardObject->TryGetNumberField(FieldName, FieldValue))
	{
		return FieldValue;
	}
	else
	{
		if (nullNotAllowed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Field %s is null or not valid integer"), *FieldName);
		}
		return 0;
	}
}

bool UCardService::GetBoolValue(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed)
{
	bool FieldValue;
	if (CardObject->HasField(FieldName) && CardObject->TryGetBoolField(FieldName, FieldValue))
	{
		return FieldValue;
	}
	else
	{
		if (nullNotAllowed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Field %s is null or not valid bool"), *FieldName);
		}
		return false;
	}
}

TSharedPtr<FJsonObject> UCardService::GetNestedObject(TSharedPtr<FJsonObject> CardObject, FString FieldName, bool nullNotAllowed)
{
	TSharedPtr<FJsonValue> nested = CardObject->GetField<EJson::Object>(FieldName);
	TSharedPtr<FJsonObject> nestedParsed = nested->AsObject();
	return nestedParsed;
}

UMinion* UCardService::GetMinionFromJson(int32 Mana, FString Name, FString GameDescription, FString IrlDescription, FString ImageFilename, int32 layer, TSharedPtr<FJsonObject> args)
{
	int32 baseAttack = GetIntValue(args, "baseAttack", false);
	int32 baseHealth = GetIntValue(args, "baseHealth", false);

	UMinion* Minion = NewObject<UMinion>();
	Minion->Init(Mana, TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*GameDescription), TCHAR_TO_UTF8(*IrlDescription), baseAttack, baseHealth, ImageFilename, layer);

	if (GetBoolValue(args, "onAttack", false))
	{
		UOnAttackModifier* Modifier = NewObject<UOnAttackModifier>();
		TSharedPtr<FJsonObject> onAttackArgs = this->GetNestedObject(args, "onAttackArgs", true);
		UEffect* Effect = ParseEffect(onAttackArgs);
		Modifier->Init(Effect);
		Minion->AddMinionModifier(Modifier);
	}

	if (int32 OnPlayId = GetIntValue(args, "onPlay", false))
	{
		USpell* Spell = Cast<USpell>(GetCardData(OnPlayId));
		if (Spell)
		{
			UOnPlayEffect* Modifier = NewObject<UOnPlayEffect>();
			UEffect* Effect = Spell->SpellEffect;
			Modifier->Init(Effect);
			Minion->AddMinionModifier(Modifier);
		}
	}

	return Minion;
}

UEffect* UCardService::ParseEffect(TSharedPtr<FJsonObject> EffectObject)
{
	FString effectType = GetStringValue(EffectObject, "effect", false);
	if (effectType == "chooseOne") {
		int32 id1 = GetIntValue(EffectObject, "id1", false);
		int32 id2 = GetIntValue(EffectObject, "id2", false);
		int32 id3 = GetIntValue(EffectObject, "id3", false);
		UChooseOneEffect* effect = NewObject<UChooseOneEffect>();
		effect->Init(this, id1, id2, id3);
		return effect;
	}
	else
	{
		return NULL;
	}
}

TArray<UMinion*> UCardService::ParseSummonMinion(TSharedPtr<FJsonObject> args)
{
	int32 Stats = GetIntValue(args, "stats", false);
	int32 Count = GetIntValue(args, "count", false);
	FString TokenName = GetStringValue(args, "name", false);
	TArray<UMinion*> Minions;
	if (GetBoolValue(args, "jadeGolem", false))
	{
		UJadeGolemMinion* Minion = NewObject<UJadeGolemMinion>();
		//Minion->AddToRoot();
		Minion->Rename(NULL, GetOuter());
		Minion->Init(1, "", "", "", 0, 0, "/Script/Engine.Texture2D'/Game/Data/Cards/ImageNotFound.ImageNotFound'", 0);
		Minions.Add(Minion);
	}
	else
	{
		for (int32 i = 0; i < Count; i++)
		{
			UMinion* Minion = NewObject<UMinion>();
			//Minion->AddToRoot();
			Minion->Rename(NULL, GetOuter()); // Necessary to ensure Minion has access to GetWorld(); other cards don't need this, because their outer is set during copying in DeckInfo
			Minion->Init(0, TCHAR_TO_UTF8(*TokenName), "", "", Stats, Stats, "/Script/Engine.Texture2D'/Game/Data/Cards/ImageNotFound.ImageNotFound'", 0);
			Minions.Add(Minion);
		}
	}
	return Minions;
}
