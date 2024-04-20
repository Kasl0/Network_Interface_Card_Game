// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleDeck.h"
#include "GameFramework/Character.h"
#include "CardBattleCharacter.generated.h"

UCLASS()
class NICGAME_API ACardBattleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACardBattleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBattleDeck* BattleDeck;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBattleDeck* GetBattleDeck();
};
