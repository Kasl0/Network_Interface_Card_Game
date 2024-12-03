// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CreateCardChoice.h"
#include "Cards/ChooseCardBase.h"
#include "Blueprint/WidgetTree.h"

UCreateCardChoice::UCreateCardChoice()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> ChooseCardWidget(TEXT("/Game/CardBattle/CardUI/ChooseCard"));
    WidgetClass = ChooseCardWidget.Class;
}

void UCreateCardChoice::CreateChoice(TArray<UCardData*> CardArray, TFunction<void(UCardData*)> CallbackFunction, UWorld* World)
{
	this->CardChosenCallback = CallbackFunction;

    if (WidgetClass == NULL)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find ChooseCard Blueprint class!"));
        return;
    }
    
    UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);
    UChooseCardBase* BaseWidget = Cast<UChooseCardBase>(Widget);
    if (!Widget)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create widget from Blueprint class!"));
        return;
    }
    BaseWidget->CardDataArray = CardArray;
    BaseWidget->Creator = this;
    BaseWidget->InitializeChoice();
    BaseWidget->AddToViewport(0);
}

void UCreateCardChoice::ChoiceMade(UCardData* Card)
{
	this->CardChosenCallback(Card);
}
