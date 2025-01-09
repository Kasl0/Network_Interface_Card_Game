#include "GamePhase/GamePhaseSubsystem.h"
#include "Dialogues/DialogueManager.h"
#include "Duel/DuelState.h"
#include "Dialogues/DialoguesProgressManager.h"


void UGamePhaseSubsystem::DuelPhase()
{
	this->ScreenWidget->ShowBoard();
	if (this->GamePhase != TEnumAsByte<EGamePhase>(Quiz))
	{
		this->GamePhase = Quiz;
		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
		UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
		if (DialoguesProgressManager->GetIsFirstGameCompleted())
		{
			if (!DialoguesProgressManager->GetIsSecondGameCompleted())
			{
				DialogueManager->CreateDialogueChain(1300, [this]() {
					UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
					UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
					UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
					DialoguesProgressManager->SetIsSecondGameCompleted();
					DialogueManager->CreateQuizChain(3, [this](int32 CorrectAnswers) {this->DuelPhase(); });
					});
			}
			else
			{
				DialogueManager->CreateQuizChain(3, [this](int32 CorrectAnswers) {this->DuelPhase(); });
			}
		}
		else
		{
			DuelPhase();
		}
	}
	else if(this->GamePhase == TEnumAsByte<EGamePhase>(Quiz))
	{
		this->GamePhase = EGamePhase::Duel;

		//this->ScreenWidget->ShowBoard();
		this->ChangeOverlay(3);

		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UDuelState* DuelState = GameInstance->GetSubsystem<UDuelState>();
			if (DuelState)
			{
				DuelState->StartDuel(TEnumAsByte(EBoardSide::Enemy));
			}
		}
	}
}

void UGamePhaseSubsystem::MapPhase()
{
	this->GamePhase = EGamePhase::Map;

	this->ScreenWidget->ShowMap();
	this->ChangeOverlay(3);
}

void UGamePhaseSubsystem::ChangeOverlay(int32 Change)
{
	if (this->ScreenWidget)
	{
		this->ScreenWidget->ChangeOverlay(GamePhase,Change);
	}
}

void UGamePhaseSubsystem::SetScreenWidget(UScreenWidget* Screen)
{
	this->ScreenWidget = Screen;
}
