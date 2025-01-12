#include "GamePhase/GamePhaseSubsystem.h"
#include "Dialogues/DialogueManager.h"
#include "Duel/DuelState.h"
#include "Dialogues/DialoguesProgressManager.h"
#include "Dialogues/RandomEncounter.h"


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
					UBattleDeck* BattleDeck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
		      DialogueManager->CreateQuizChain(3, [this, BattleDeck](int32 CorrectAnswers) {this->QuizCB(CorrectAnswers, BattleDeck);});
					});
			}
			else
			{
				UBattleDeck* BattleDeck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
		    DialogueManager->CreateQuizChain(3, [this, BattleDeck](int32 CorrectAnswers) {this->QuizCB(CorrectAnswers, BattleDeck);});
			}
		}
		else
		{
			DuelPhase();
		}
	}
}

void UGamePhaseSubsystem::StartDuel(UBattleDeck* BattleDeck)
{
	if (this->GamePhase == TEnumAsByte<EGamePhase>(Quiz))
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
				DuelState->StartDuel(TEnumAsByte(EBoardSide::Enemy), BattleDeck);
			}
		}
	}
}

void UGamePhaseSubsystem::EncounterPhase()
{
	this->GamePhase = EGamePhase::Encounter;

	URandomEncounter* Encounter = NewObject<URandomEncounter>();
	Encounter->CreateRandomEncounter(GetWorld());
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
		this->ScreenWidget->ChangeOverlay(GamePhase, Change);
	}
}

void UGamePhaseSubsystem::SetScreenWidget(UScreenWidget* Screen)
{
	this->ScreenWidget = Screen;
}

void UGamePhaseSubsystem::QuizCB(int32 CorrectAnswers, UBattleDeck* BattleDeck)
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	BattleDeck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
	BattleDeck->InitializeDeck(GetWorld());
	TArray<UCardData*> CardDataArray = BattleDeck->GetDataArray();
	if (CorrectAnswers > 0) {
		// one correct answer -> health bonus for all cards
		for (int i = 0; i < CardDataArray.Num(); i++) {
			if (CardDataArray[i]->IsA(UMinion::StaticClass())) {
				UMinion* ActiveMinion = Cast<UMinion>(CardDataArray[i]);
				ActiveMinion->BaseHealth++;
				ActiveMinion->CurrentHealth++;
			}
		}
	}
	if (CorrectAnswers > 1) {
		// two correct answers -> attack bonus for all cards
		for (int i = 0; i < CardDataArray.Num(); i++) {
			if (CardDataArray[i]->IsA(UMinion::StaticClass())) {
				UMinion* ActiveMinion = Cast<UMinion>(CardDataArray[i]);
				ActiveMinion->BaseAttack++;
			}
		}
	}
	if (CorrectAnswers > 2) {
		// three correct answers -> mana cost decrease for all cards
		for (int i = 0; i < CardDataArray.Num(); i++) {
			CardDataArray[i]->CardCost--;
		}
	}
	this->StartDuel(BattleDeck);
}