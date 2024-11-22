// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueManager.h"
#include "Misc/FileHelper.h"
#include "JsonObjectConverter.h"

UDialogueManager::UDialogueManager()
{
    // Konstruktor
}

TArray<FDialogueOption> UDialogueManager::GetDialogues() const
{
    return Dialogues;
}

bool UDialogueManager::LoadDialoguesFromFile(const FString& FilePath)
{
    FString JsonString;

    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Nie uda�o si� za�adowa� pliku JSON."));
        return false;
    }

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        TArray<TSharedPtr<FJsonValue>> JsonDialogues = JsonObject->GetArrayField("dialogues");

        Dialogues.Empty();

        for (const TSharedPtr<FJsonValue>& DialogueValue : JsonDialogues)
        {
            FDialogueOption DialogueOption;
            TSharedPtr<FJsonObject> DialogueObject = DialogueValue->AsObject();

            // Wczytanie identyfikatora klasy dialogu
            DialogueOption.ClassID = DialogueObject->GetIntegerField("class_id");

            // Wczytanie pytania
            DialogueOption.Question = DialogueObject->GetStringField("question");

            // Wczytanie odpowiedzi jako s�ownik
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

    UE_LOG(LogTemp, Error, TEXT("B��d parsowania pliku JSON."));
    return false;
}