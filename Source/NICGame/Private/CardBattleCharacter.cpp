// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBattleCharacter.h"

#include "DeckInfo.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACardBattleCharacter::ACardBattleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = true;*/

}

// Called when the game starts or when spawned
void ACardBattleCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->BattleDeck = NewObject<UBattleDeck>();
	this->BattleDeck->AddToRoot();
}

// Called every frame
void ACardBattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACardBattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBattleDeck* ACardBattleCharacter::GetBattleDeck()
{
	return this->BattleDeck;
}
