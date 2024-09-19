// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapWidget.h"

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* Game = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (Game)
	{
		this->MapState = Cast<UMapState>(Game->GetSubsystem<UMapState>());
	}

	this->DrawMap();
}
