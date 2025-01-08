// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueManager.h"
#include "Misc/FileHelper.h"
#include "Blueprint/UserWidget.h"
#include "Dialogues/DialogueWidget.h"
#include "JsonObjectConverter.h"
#include "Taxonomy/TaxonomySubsystem.h"

#include <random>

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
    if (AnswerKey != "" || Dialogue.Type == TEnumAsByte<EDialogueType>(Info))
    {
        this->ChoiceHandler->Init(GetWorld());
        this->ChoiceHandler->HandleChoice(Dialogue.Outcomes[AnswerKey]);

        if (Dialogue.Type == TEnumAsByte<EDialogueType>(QuizDialogue))
        {
            UGameInstance* Ins = Cast<UGameInstance>(GetWorld()->GetGameInstance());
            UTaxonomySubsystem* TaxonomySubsystem = Cast<UTaxonomySubsystem>(Ins->GetSubsystem<UTaxonomySubsystem>());

            if (Dialogue.Outcomes[AnswerKey] == "correct") 
            {
                CorrectAnswers++;
                TaxonomySubsystem->QuestionAnswered(true);
            }
            else
            {
                TaxonomySubsystem->QuestionAnswered(false);
            }
        }

        int32 NextQuestionID = Dialogue.NextQuestion[AnswerKey];
        if (NextQuestionID == -1)
        {
            if (Dialogue.Type != TEnumAsByte<EDialogueType>(QuizDialogue) && CurrentCallback)
            {
                auto Callback = CurrentCallback;
                this->CurrentCallback = NULL;
                Callback();
            }
            else if (Dialogue.Type == TEnumAsByte<EDialogueType>(QuizDialogue) && QuizCallback)
            {
                auto Callback = QuizCallback;
                this->QuizCallback = NULL;
                Callback(CorrectAnswers);
            }
        }
        else
        {
            this->CreateDialogueWidget(NextQuestionID);
        }
    }
}

void UDialogueManager::CreateDialogueChain(int32 FirstId, TFunction<void()> Callback)
{
    this->CurrentCallback = Callback;
    this->CreateDialogueWidget(FirstId);
}

void UDialogueManager::CreateQuizChain(int32 Count, TFunction<void(int32)> Callback)
{
    this->QuizCallback = Callback;
    this->CorrectAnswers = 0;

    if (Count < 1 || 5 < Count)
    {
        Callback(0); // arbitrary count limits
    }


    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> rng(0, std::max(QuizIndexes.Num() - 1, 0)); // define the range
    

    TSet<int32> ChosenQuestions;
    while (ChosenQuestions.Num() < Count && QuizIndexes.Num() >= Count){
        int32 number = rng(gen);
        if (true) // add any necessary checks
        {
            ChosenQuestions.Add(number);
        }
    }
    
    int32 NextQuestionId = -1;
    for (int32 QuizIndex : ChosenQuestions)
    {
        int32 QuestionId = QuizIndexes[QuizIndex];
        Dialogues[QuestionId].NextQuestion.Add("0", NextQuestionId);
        Dialogues[QuestionId].NextQuestion.Add("1", NextQuestionId);
        Dialogues[QuestionId].NextQuestion.Add("2", NextQuestionId);
        Dialogues[QuestionId].NextQuestion.Add("3", NextQuestionId);
        NextQuestionId = QuestionId;
    }

    if (NextQuestionId != -1)
    {
        CreateDialogueWidget(NextQuestionId);
    }
    else
    {
        Callback(0);
    }
}

void UDialogueManager::CreateDialogueWidget(int32 Id)
{
    FDialogueOption Option = GetDialogueById(Id);
    if (DialogueWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);
        UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(Widget);
        if (!DialogueWidget)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create widget from Blueprint class!"));
            return;
        }
        DialogueWidget->DialogueManager = this;
        DialogueWidget->SetDialogue(Option);
        DialogueWidget->AddToViewport();
    }
}

UDialogueManager::UDialogueManager()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> DialogueWidget(TEXT("/Game/Dialogues/BP_DialogueWidget"));
    if (DialogueWidget.Class == NULL)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find DialogueWidget Blueprint class!"));
    }
    else
    {
        DialogueWidgetClass = DialogueWidget.Class;
    }
}

void UDialogueManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    LoadDialoguesFromFile(FPaths::ProjectContentDir() + TEXT("Dialogues/Dialogues.json"));

    ChoiceHandler = NewObject<UDialogueChoiceHandler>();
    //ChoiceHandler->Init(GetWorld());
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

        int32 i = 0; // Dialogue index
        for (const TSharedPtr<FJsonValue>& DialogueValue : JsonDialogues)
        {
            FDialogueOption DialogueOption;
            TSharedPtr<FJsonObject> DialogueObject = DialogueValue->AsObject();

            // Wczytanie identyfikatora klasy dialogu
            DialogueOption.ClassID = DialogueObject->GetIntegerField("class_id");

            // Wczytanie pytania
            DialogueOption.Question = DialogueObject->GetStringField("question");

            // Typ dialogu
            FString Type = DialogueObject->GetStringField("type");
            if (Type == "Info")
            {
                DialogueOption.Type = Info;
            }
            else if (Type == "Dialogue")
            {
                DialogueOption.Type = Dialogue;
            }
            else if (Type == "Quiz")
            {
                DialogueOption.Type = QuizDialogue;
                this->QuizIndexes.Add(i);
            }

            // Wczytanie odpowiedzi jako słownik
            TSharedPtr<FJsonObject> JsonAnswersObject = DialogueObject->GetObjectField("answers");
            for (const auto& AnswerPair : JsonAnswersObject->Values)
            {
                FString Key = AnswerPair.Key;
                FString AnswerText = AnswerPair.Value->AsString();
                DialogueOption.Answers.Add(Key, AnswerText);
            }

            // Konsekwencje odpowiedzi
            TSharedPtr<FJsonObject> OutcomesObject = DialogueObject->GetObjectField("outcomes");
            for (const auto& OutcomePair : OutcomesObject->Values)
            {
                FString Key = OutcomePair.Key;
                FString AnswerText = OutcomePair.Value->AsString();
                DialogueOption.Outcomes.Add(Key, AnswerText);
            }

            // ID następnego dialogu w zależności od odpowiedzi
            TSharedPtr<FJsonObject> NextQuestionObject = DialogueObject->GetObjectField("nextQuestion");
            for (const auto& NextQuestionPair : NextQuestionObject->Values)
            {
                FString Key = NextQuestionPair.Key;
                int32 AnswerText = NextQuestionPair.Value->AsNumber();
                DialogueOption.NextQuestion.Add(Key, AnswerText);
            }

            Dialogues.Add(DialogueOption);
            i++;
        }

        return true;
    }

    UE_LOG(LogTemp, Error, TEXT("Błąd parsowania pliku JSON."));
    return false;
}