// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogues/RandomEncounter.h"
#include "Dialogues/DialogueManager.h"
#include "GamePhase/GamePhaseSubsystem.h"
#include <random>

TArray<int32> URandomEncounter::EncounterIds = {
	3000, 3001
};

int32 URandomEncounter::GetRandomEncounterId()
{
	if (EncounterIds.Num() > 0)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> rng(0, EncounterIds.Num() - 1); // define the range

		return EncounterIds[rng(gen)];
	}
	else
	{
		return -1;
	}
}

void URandomEncounter::CreateRandomEncounter(UWorld* World)
{
	this->WorldPointer = World;

	UGameInstance* Instance = Cast<UGameInstance>(World->GetGameInstance());
	UDialogueManager* Dialogues = Cast<UDialogueManager>(Instance->GetSubsystem<UDialogueManager>());

	this->CurrentEncounterId = GetRandomEncounterId();
	if (this->CurrentEncounterId != -1)
	{
		Dialogues->CreateDialogueChain(CurrentEncounterId, [this]() { this->AfterEncounter(); });
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find Random Encounter ID"));
		AfterEncounter();
	}
}

void URandomEncounter::AfterEncounter()
{
	EncounterIds.Remove(CurrentEncounterId);

	this->CurrentEncounterId = -1;

	UGameInstance* Instance = Cast<UGameInstance>(WorldPointer->GetGameInstance());
	UGamePhaseSubsystem* GamePhase = Cast<UGamePhaseSubsystem>(Instance->GetSubsystem<UGamePhaseSubsystem>());

	GamePhase->MapPhase();
}
