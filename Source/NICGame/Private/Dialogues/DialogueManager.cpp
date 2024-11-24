// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueManager.h"
#include "Misc/FileHelper.h"
#include "Blueprint/UserWidget.h"
#include "Dialogues/DialogueWidget.h"
#include "JsonObjectConverter.h"

TArray<FDialogueOption> UDialogueManager::GetDialogues()
{
    return Dialogues;
}

FDialogueOption UDialogueManager::GetDialogueById(int32 Id)
{
    for (auto Option : Dialogues) {
        if (Option.ClassID == Id)
        {
            return Option;
        }
    }
    return FDialogueOption();
}



void UDialogueManager::HandleDialogueChoice(FDialogueOption Dialogue, FString AnswerKey)
{

}

void UDialogueManager::CreateDialogueWidget(int32 Id)
{
    FDialogueOption Option = GetDialogueById(Id);
    if (DialogueWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);
        UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(Widget);
        if (DialogueWidget)
        {
            DialogueWidget->SetDialogue(Option);
            DialogueWidget->AddToViewport();
        }
    }
}

UDialogueManager::UDialogueManager()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> DialogueWidget(TEXT("/Game/Dialogue/BP_DialogueWidget"));
    if (DialogueWidget.Class == NULL)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find DialogueWidget Blueprint class!"));
    }
    else 
    {
        DialogueWidgetClass = DialogueWidget.Class;
    }

    LoadDialoguesFromFile(FPaths::ProjectContentDir() + TEXT("Dialogues/Dialogues.json"));
}

bool UDialogueManager::LoadDialoguesFromFile(const FString FilePath)
{
    FString JsonString;

    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Couldn't load JSON file."));
        return false;
    }

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    TArray<TSharedPtr<FJsonValue>> JsonDialogues;

    if (FJsonSerializer::Deserialize(Reader, JsonDialogues))
    {
        //TArray<TSharedPtr<FJsonValue>> JsonDialogues = JsonObject->GetArrayField("dialogues");

        Dialogues.Empty();

        for (const TSharedPtr<FJsonValue>& DialogueValue : JsonDialogues)
        {
            FDialogueOption DialogueOption;
            TSharedPtr<FJsonObject> DialogueObject = DialogueValue->AsObject();

            // Wczytanie identyfikatora klasy dialogu
            DialogueOption.ClassID = DialogueObject->GetIntegerField("class_id");

            // Wczytanie pytania
            DialogueOption.Question = DialogueObject->GetStringField("question");

            // Wczytanie odpowiedzi jako słownik
            TSharedPtr<FJsonObject> JsonAnswersObject = DialogueObject->GetObjectField("answers");
            for (const auto& AnswerPair : JsonAnswersObject->Values)
            {
                FString Key = AnswerPair.Key;
                FString AnswerText = AnswerPair.Value->AsString();
                DialogueOption.Answers.Add(Key, AnswerText);
            }

            Dialogues.Add(DialogueOption);
        }

        return true;
    }

    UE_LOG(LogTemp, Error, TEXT("Błąd parsowania pliku JSON."));
    return false;
}