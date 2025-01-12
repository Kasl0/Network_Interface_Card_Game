// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePhase/GamePhaseSubsystem.h"
#include "Dialogues/DialogueManager.h"
#include "Duel/DuelState.h"


void UGamePhaseSubsystem::DuelPhase()
{
	this->ScreenWidget->ShowBoard();
	if (this->GamePhase != TEnumAsByte<EGamePhase>(Quiz))
	{
		this->GamePhase = Quiz;
		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
		UBattleDeck* BattleDeck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
		DialogueManager->CreateQuizChain(3, [this, BattleDeck](int32 CorrectAnswers) {this->QuizCB(CorrectAnswers, BattleDeck);}); // Give buffs to player based on quiz result
		//DialogueManager->CreateDialogueChain(1, [this]() {this->DuelPhase(); });
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