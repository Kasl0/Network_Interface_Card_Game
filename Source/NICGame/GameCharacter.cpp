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

	// Set default table location vector
	TableLocation = FVector(0.0f, 0.0f, 0.0f);
	IsAtTable = false;
	TableCameraDownRotation = FRotator(40.0f, 0.0f, 0.0f);
	TableCameraTiltDirection = 0;
	TableCameraTiltRotation = FRotator(15.0f, 30.0f, 0.0f);
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
	if (IsAtTable and TableCameraTiltDirection > -1)
	{
		if (TableCameraTiltDirection == 1)
		{
			newRotation -= TableCameraTiltRotation;
		}
		else
		{
			newRotation -= FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
		}
		TableCameraTiltDirection--;
	}
	else if (!IsAtTable)
	{
		newRotation -= FRotator(0.0f, 90.0f, 0.0f);
	}
	SetActorRotation(newRotation);
}

void AGameCharacter::TurnRight(const FInputActionInstance& Instance)
{
	FRotator newRotation = GetActorRotation();
	if (IsAtTable and TableCameraTiltDirection < 1)
	{
		if (TableCameraTiltDirection == -1)
		{
			newRotation += FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
		}
		else
		{
			newRotation += TableCameraTiltRotation;
		}
		TableCameraTiltDirection++;
	}
	else if (!IsAtTable)
	{
		newRotation += FRotator(0.0f, 90.0f, 0.0f);
	}
	SetActorRotation(newRotation);
}

void AGameCharacter::MoveForward(const FInputActionInstance& Instance)
{
	if (!IsAtTable)
	{
		FVector newLocation = GetActorLocation();
		FVector forwardVector = GetActorForwardVector();
		newLocation += (forwardVector * DistanceToMove);

		if (newLocation.Equals(TableLocation) and GetActorRotation().Equals(FRotator(0.0f, 90.0f, 0.0f)))
		{
			IsAtTable = true;
			FRotator newRotation = GetActorRotation();
			newRotation -= TableCameraDownRotation;
			SetActorRotation(newRotation);
		}
		SetActorLocation(newLocation);
	}
}

void AGameCharacter::MoveBackward(const FInputActionInstance& Instance)
{
	if (IsAtTable and TableCameraTiltDirection != 0)
	{
		FRotator newRotation = GetActorRotation();
		newRotation -= FRotator(TableCameraTiltRotation.Pitch, TableCameraTiltDirection * TableCameraTiltRotation.Yaw, TableCameraTiltDirection * TableCameraTiltRotation.Roll);
		SetActorRotation(newRotation);
		TableCameraTiltDirection = 0;
	}
	else if (IsAtTable and TableCameraTiltDirection == 0)
	{
		FRotator newRotation = GetActorRotation();
		newRotation += TableCameraDownRotation;
		SetActorRotation(newRotation);
		IsAtTable = false;
	}
	if (!IsAtTable) {
		FVector newLocation = GetActorLocation();
		FVector forwardVector = GetActorForwardVector();
		newLocation -= (forwardVector * DistanceToMove);
		SetActorLocation(newLocation);
	}
}
