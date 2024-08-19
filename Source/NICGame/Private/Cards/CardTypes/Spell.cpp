#include "Cards/CardTypes/Spell.h"
#include "Duel/DuelState.h"
#include "Duel/Board/BoardState.h"

void USpell::Init(UEffect* Effect)
{
	this->SpellEffect = Effect;
	this->SpellEffect->AddToRoot();
}

bool USpell::IsPlayable(EBoardSide Side)
{
	if (!Super::IsPlayable(Side))
	{
		return false;
	}
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	return !DuelState->GetBoardState()->IsBoardSideEmpty(Side);
}

void USpell::Apply(UObject* SpellTarget)
{
	this->SpellEffect->Apply(SpellTarget);
}
