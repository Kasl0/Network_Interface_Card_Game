#include "Cards/CardHUDWidget.h"
#include "Components/Button.h"
#include <Cards/CardWidget.h>
#include "Duel/EBoardSide.h"
#include "Cards/CardHandWidget.h"
#include "Duel/DuelState.h"

void UCardHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		this->DuelState = GameInstance->GetSubsystem<UDuelState>();
		if (this->DuelState && !this->DuelState->IsDuelInProgress())
		{
			if (this->DrawCardButton)
			{
				this->DrawCardButton->OnClicked.AddDynamic(this, &UCardHUDWidget::DrawCard);
			}

			if (this->EndTurnButton)
			{
				this->EndTurnButton->OnClicked.AddDynamic(this, &UCardHUDWidget::EndTurn);
			}
			this->DuelState->StartDuel(TEnumAsByte(Enemy));
		}
	}
}


void UCardHUDWidget::DrawCard()
{
	this->CardHand->DrawCard();
}

void UCardHUDWidget::EndTurn()
{
	if (this->DuelState)
	{
		this->DuelState->SwitchPlayerTurn();
	}
}
