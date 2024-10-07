#include "Duel/Board/UpcomingCardSlotWidgetWithActors.h"

bool UUpcomingCardSlotWidgetWithActors::IsOccupied()
{
	return this->CardSlot->IsOccupied();
}

ACardActor* UUpcomingCardSlotWidgetWithActors::GetCard()
{
	return this->CardSlot->GetCard();
}
