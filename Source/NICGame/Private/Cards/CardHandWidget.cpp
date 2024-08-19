#include "Cards/CardHandWidget.h"
#include "Duel/DuelState.h"
#include "Deck/BattleDeck.h"

void UCardHandWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UDuelState* DuelState = GameInstance->GetSubsystem<UDuelState>();
		if (DuelState && !DuelState->IsDuelInProgress())
		{
			UCardHand* CardHand = Cast<UCardHand>(GameInstance->GetSubsystem<UCardHand>());
			CardHand->OnCardHandAdd.AddDynamic(this, &UCardHandWidget::OnCardHandAdded);
			CardHand->OnCardHandRemove.AddDynamic(this, &UCardHandWidget::OnCardHandRemoved);
		}
	}
}

void UCardHandWidget::OnCardHandAdded(UCardData* CardData)
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UCardHand* CardHand = Cast<UCardHand>(GameInstance->GetSubsystem<UCardHand>());
	this->CreateCardWidget(CardData);
}

void UCardHandWidget::OnCardHandRemoved(UCardData* CardData)
{
	this->RemoveCardByCardData(CardData);
}
