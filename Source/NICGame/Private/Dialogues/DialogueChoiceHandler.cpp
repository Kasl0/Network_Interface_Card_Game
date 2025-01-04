// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueChoiceHandler.h"
#include "Taxonomy/TaxonomySubsystem.h"
#include "Dialogues/DialogueManager.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardService.h"
#include "Deck/DeckInfo.h"
#include "Cards/CreateCardChoice.h"

void UDialogueChoiceHandler::Init(UWorld* ParentWorld)
{
    World = ParentWorld;

    // Add any necessary consequences, e.g. removing a random card from the deck, buffing one card for the rest of the game etc.
    ChoiceToFunctionMap = {
        {"x+", &UDialogueChoiceHandler::HandleBartle},
        {"x-", &UDialogueChoiceHandler::HandleBartle},
        {"y+", &UDialogueChoiceHandler::HandleBartle},
        {"y-", &UDialogueChoiceHandler::HandleBartle},
        //{"card", &UDialogueChoiceHandler::HandleBartle},
        {"quiz", &UDialogueChoiceHandler::CreateQuiz},
        //{"quizToken", &UDialogueChoiceHandler::HandleBartle},
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

void UDialogueChoiceHandler::ChooseCard(FString Choice)
{
    auto Callback = [this](UCardData* CardData) {
        UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
        UDeckInfo* DeckInfo = Cast<UDeckInfo>(GameInstance->GetSubsystem<UDeckInfo>());
        DeckInfo->AddCardToDeck(CardData);
    };

    UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
    UCardService* CardService = Cast<UCardService>(GameInstance->GetSubsystem<UCardService>());
    TArray<UCardData*> CardsToChoose = {// Hardcoded for now, should be changed to picking 3 cards at random
        CardService->GetCardData(1), 
        CardService->GetCardData(1),
        CardService->GetCardData(1),
    };

    UCreateCardChoice* CardChoice = NewObject<UCreateCardChoice>();
    CardChoice->CreateChoice(CardsToChoose, Callback, this->World);
}

void UDialogueChoiceHandler::CreateQuiz(FString Choice)
{
    auto Callback = [this](int32 CorrectAnswers) {
        if (CorrectAnswers == 1)
        {
            UE_LOG(LogTemp, Warning, TEXT("1 correct choice"));
        }
        else if (CorrectAnswers == 2)
        {
            UE_LOG(LogTemp, Warning, TEXT("2 correct choices"));
        }
        else if (CorrectAnswers == 3)
        {
            UE_LOG(LogTemp, Warning, TEXT("3 correct choices"));
        }
    };

    UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
    UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());

    DialogueManager->CreateQuizChain(3, Callback);
}

void UDialogueChoiceHandler::AddQuizToken(FString Choice)
{
    // Add a token that allows user to repeat 1 quiz
}
