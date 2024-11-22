// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"

void UDialogueWidget::InitializeAnswers(const TMap<FString, FString>& Answers)
{
    if (!AnswersBox) return;  // Upewnij siê, ¿e VerticalBox jest poprawnie przypisany

    // Wyczyœæ wczeœniejsze przyciski z AnswersBox
    AnswersBox->ClearChildren();

    for (const auto& Answer : Answers)
    {
        // Stworzenie przycisku
        UButton* AnswerButton = NewObject<UButton>(this);
        UTextBlock* ButtonText = NewObject<UTextBlock>(AnswerButton);

        if (ButtonText)
        {
            // Ustawienie tekstu przycisku na klucz z mapy odpowiedzi
            ButtonText->SetText(FText::FromString(Answer.Key));
            AnswerButton->AddChild(ButtonText);
        }

        // Mo¿esz dodaæ akcjê na klikniêcie przycisku, np. wywo³anie metody po klikniêciu
        AnswerButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnAnswerClicked);

        // Dodanie przycisku do VerticalBox
        AnswersBox->AddChild(AnswerButton);
    }
}

void UDialogueWidget::OnAnswerClicked()
{
    // Tutaj mo¿esz dodaæ akcjê po klikniêciu odpowiedzi
    // Na przyk³ad: wyœwietlenie odpowiedzi, przejœcie do nastêpnego dialogu itd.
}