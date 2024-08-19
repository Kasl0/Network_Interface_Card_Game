#include "Cards/CardTypes/CardData.h"
#include "Duel/DuelState.h"
#include "Duel/DuelCharacter.h"

#include <string>

void UCardData::SetData(uint8 Cost, std::string Name, std::string Description)
{
	this->CardCost = Cost;
	this->CardName = FText::FromString(UTF8_TO_TCHAR(Name.c_str()));
	this->CardDescription = FText::FromString(UTF8_TO_TCHAR(Description.c_str()));
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
