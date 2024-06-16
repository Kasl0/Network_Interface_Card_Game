#include "Cards/CardTypes/CardData.h"

#include <string>

void UCardData::SetData(uint8 Cost, std::string Name, std::string Description)
{
	this->CardCost = Cost;
	this->CardName = FText::FromString(UTF8_TO_TCHAR(Name.c_str()));
	this->CardDescription = FText::FromString(UTF8_TO_TCHAR(Description.c_str()));
}