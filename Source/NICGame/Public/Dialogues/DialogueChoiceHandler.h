// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueChoiceHandler.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDialogueChoiceHandler : public UObject
{
	GENERATED_BODY()
	
	using MemberFunctionPtr = void(UDialogueChoiceHandler::*)(FString);
	TMap<FString, MemberFunctionPtr> ChoiceToFunctionMap;

	UPROPERTY()
	UWorld* World;

	void HandleBartle(FString Choice);

	void ChooseCard(FString Choice);

	void CreateQuiz(FString Choice);
	
	void AddQuizToken(FString Choice);


public:
	void Init(UWorld* ParentWorld);

	void HandleChoice(FString Choice);
};
