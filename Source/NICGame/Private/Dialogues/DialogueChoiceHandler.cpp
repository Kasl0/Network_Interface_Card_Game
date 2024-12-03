// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueChoiceHandler.h"
#include "Taxonomy/TaxonomySubsystem.h"

void UDialogueChoiceHandler::Init(UWorld* ParentWorld)
{
    World = ParentWorld;

    // Add any necessary consequences, e.g. removing a random card from the deck, buffing one card for the rest of the game etc.
    ChoiceToFunctionMap = {
        {"x+", &UDialogueChoiceHandler::HandleBartle},
        {"x-", &UDialogueChoiceHandler::HandleBartle},
        {"y+", &UDialogueChoiceHandler::HandleBartle},
        {"y-", &UDialogueChoiceHandler::HandleBartle},
    };
}

void UDialogueChoiceHandler::HandleChoice(FString Choice)
{
    TArray<FString> Subchoices;
    Choice.ParseIntoArray(Subchoices, TEXT(";"), /*bCullEmpty=*/true);

    for (const FString& Substring : Subchoices)
    {
        if (MemberFunctionPtr* FuncPtr = ChoiceToFunctionMap.Find(Substring))
        {
            (this->**(FuncPtr))(Substring);
        }
        else if (!Substring.Equals(""))
        {
            UE_LOG(LogTemp, Warning, TEXT("No handler found for choice: %s"), *Substring);
        }
    }
}

void UDialogueChoiceHandler::HandleBartle(FString Choice)
{
    UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
    UTaxonomySubsystem* Taxonomy = Cast<UTaxonomySubsystem>(GameInstance->GetSubsystem<UTaxonomySubsystem>());

    if (Choice.Equals("x+"))
    {
        Taxonomy->ChangeXAxisValue(1);
        UE_LOG(LogTemp, Warning, TEXT("Bartle choice: x+"));
    }
    else if (Choice.Equals("x-"))
    {
        Taxonomy->ChangeXAxisValue(-1);
        UE_LOG(LogTemp, Warning, TEXT("Bartle choice: x-"));
    }
    else  if (Choice.Equals("y+"))
    {
        Taxonomy->ChangeYAxisValue(1);
        UE_LOG(LogTemp, Warning, TEXT("Bartle choice: y+"));
    }
    else if (Choice.Equals("y-"))
    {
        Taxonomy->ChangeYAxisValue(-1);
        UE_LOG(LogTemp, Warning, TEXT("Bartle choice: y-"));
    }
}
