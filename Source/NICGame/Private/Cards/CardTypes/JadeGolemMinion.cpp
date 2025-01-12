// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardTypes/JadeGolemMinion.h"

int32 UJadeGolemMinion::Stats;

void UJadeGolemMinion::Init(uint8 Cost, std::string Name, std::string GameDescription, std::string IrlDescription, int32 Attack, int32 Health, FString Image, int32 Layer)
{
	this->CardCost = 1;
	this->CardName = FText::FromString("Wezel Sieci");
	this->CardGameDescription = FText::FromString("");
	this->CardIrlDescription = FText::FromString("");
	this->CardLayer = 0;
	this->SetCardImage(Image);

	this->BaseAttack = Stats;
	this->BaseHealth = Stats;
	this->CurrentHealth = this->BaseHealth;
	UJadeGolemMinion::Stats += 1;
}
