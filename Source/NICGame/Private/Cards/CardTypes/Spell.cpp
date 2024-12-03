#include "Cards/CardTypes/Spell.h"
#include "Duel/DuelState.h"
#include "Duel/Board/BoardState.h"

void USpell::Init(UEffect* Effect)
{
	this->SpellEffect = Effect;
}

bool USpell::IsPlayable(EBoardSide Side)
{
	if (!Super::IsPlayable(Side))
	{
		return false;
	}
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
	if (SpellEffect->Target == TEnumAsByte<EEffectTarget>(Minion))
	{
		return !DuelState->GetBoardState()->IsBoardSideEmpty(Side);
	}
	else
	{
		return true;
	}
}

void USpell::Apply(UObject* SpellTarget)
{
	this->SpellEffect->Apply(SpellTarget);
}
