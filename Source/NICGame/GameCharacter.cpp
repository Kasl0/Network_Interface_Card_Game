// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Set default forward/backward movement distance
	DistanceToMove = 100.0f;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (TurnLeftAction)
		{
			Input->BindAction(TurnLeftAction, ETriggerEvent::Triggered, this, &AGameCharacter::TurnLeft);
		}
		if (TurnRightAction)
		{
			Input->BindAction(TurnRightAction, ETriggerEvent::Triggered, this, &AGameCharacter::TurnRight);
		}
		if (MoveForwardAction)
		{
			Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AGameCharacter::MoveForward);
		}
		if (MoveBackwardAction)
		{
			Input->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &AGameCharacter::MoveBackward);
		}
	}
}

void AGameCharacter::TurnLeft(const FInputActionInstance& Instance)
{
	FRotator newRotation = GetActorRotation();
	newRotation += FRotator(0.0f, -90.0f, 0.0f);
	SetActorRotation(newRotation);
}

void AGameCharacter::TurnRight(const FInputActionInstance& Instance)
{
	FRotator newRotation = GetActorRotation();
	newRotation += FRotator(0.0f, 90.0f, 0.0f);
	SetActorRotation(newRotation);
}

void AGameCharacter::MoveForward(const FInputActionInstance& Instance)
{
	FVector newLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	newLocation += (forwardVector * DistanceToMove);
	SetActorLocation(newLocation);
}

void AGameCharacter::MoveBackward(const FInputActionInstance& Instance)
{
	FVector newLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	newLocation -= (forwardVector * DistanceToMove);
	SetActorLocation(newLocation);
}
