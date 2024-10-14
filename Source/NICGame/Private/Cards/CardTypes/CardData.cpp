#include "Cards/CardTypes/CardData.h"
#include "Duel/DuelState.h"
#include "Duel/DuelCharacter.h"

#include <string>

void UCardData::SetData(uint8 Cost, std::string Name, std::string Description, FString ImageFilename)
{
	this->CardCost = Cost;
	this->CardName = FText::FromString(UTF8_TO_TCHAR(Name.c_str()));
	this->CardDescription = FText::FromString(UTF8_TO_TCHAR(Description.c_str()));
	this->SetCardImage(ImageFilename);
}

void UCardData::SetCardImage(FString ImageFilename)
{
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImageFilename));
	if (Texture)
	{
		CardBrush.SetResourceObject(Texture);
		float ImageWidth = FMath::Min(512.0f, (float)Texture->GetSizeX());
		float ImageHeight = FMath::Min(512.0f, (float)Texture->GetSizeY());
		float AspectRatio = ImageWidth / ImageHeight;
		if (AspectRatio > 1.0f)
		{
			CardBrush.ImageSize = FVector2D(512.0f, 512.0f / AspectRatio);
		}
		else
		{
			CardBrush.ImageSize = FVector2D(512.0f * AspectRatio, 512.0f);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not load texture from file"));
	}
}

bool UCardData::IsPlayable(EBoardSide Side)
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	UDuelCharacter* CurrentTurnCharacter = DuelState->GetCurrentTurnCharacter();
	if (CurrentTurnCharacter == nullptr)
	{
		return false;
	}
	return this->CardCost <= CurrentTurnCharacter->GetCurrentMana();
}
