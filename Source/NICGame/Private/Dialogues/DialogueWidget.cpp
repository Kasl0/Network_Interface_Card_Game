// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"

void UDialogueWidget::InitializeAnswers(const TMap<FString, FString>& Answers)
{
    if (!AnswersBox) return;  // Upewnij si�, �e VerticalBox jest poprawnie przypisany

    // Wyczy�� wcze�niejsze przyciski z AnswersBox
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

        // Mo�esz doda� akcj� na klikni�cie przycisku, np. wywo�anie metody po klikni�ciu
        AnswerButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnAnswerClicked);

        // Dodanie przycisku do VerticalBox
        AnswersBox->AddChild(AnswerButton);
    }
}

void UDialogueWidget::OnAnswerClicked()
{
    // Tutaj mo�esz doda� akcj� po klikni�ciu odpowiedzi
    // Na przyk�ad: wy�wietlenie odpowiedzi, przej�cie do nast�pnego dialogu itd.
}