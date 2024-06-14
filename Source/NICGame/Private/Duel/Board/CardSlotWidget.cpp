#include "Duel/Board/CardSlotWidget.h"

bool UCardSlotWidget::IsOccupied()
{
	return this->Overlay->GetChildAt(1) != NULL;
}

UCardWidget* UCardSlotWidget::GetCardWidget()
{
	return Cast<UCardWidget>(this->Overlay->GetChildAt(1));
}
