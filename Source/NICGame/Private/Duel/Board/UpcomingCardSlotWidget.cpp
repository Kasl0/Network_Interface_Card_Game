#include "Duel/Board/UpcomingCardSlotWidget.h"

bool UUpcomingCardSlotWidget::IsOccupied()
{
	return this->CardSlot->IsOccupied();
}

UCardWidget* UUpcomingCardSlotWidget::GetCardWidget()
{
	return this->CardSlot->GetCardWidget();
}
