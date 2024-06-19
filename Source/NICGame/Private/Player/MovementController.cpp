#include "Player/MovementController.h"
#include "Player/GameCharacter.h"

// Sets default values for this component's properties
UMovementController::UMovementController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default desired transform
	bMoveToDesiredTransform = false;
	DesiredLocation = FVector(0.0f, 0.0f, 0.0f);
	DesiredRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Set default forward/backward movement distance
	DistanceToMove = 150.0f;

	// Set default table location vector
	TableLocation = FVector(166.0f, -213.0f, 125.0f);
	TableRotation = FRotator(0.0f, 180.0f, 0.0f);
	IsAtTable = false;
	TableCameraTranslation = FVector(-10.0f, 0.0f, 12.0f);
	TableCameraDownRotation = FRotator(54.0f, 0.0f, 0.0f);
	TableCameraTiltDirection = 0;
	TableCameraTiltRotation = FRotator(15.0f, 30.0f, 0.0f);
}


// Called when the game starts
void UMovementController::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	DesiredLocation = Owner->GetActorLocation();
	DesiredRotation = Owner->GetActorRotation();
}


// Called every frame
void UMovementController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bMoveToDesiredTransform)
	{
		FVector currentLocation = GetOwner()->GetActorLocation();
		FRotator currentRotation = GetOwner()->GetActorRotation();

		FVector NewLocation = FMath::VInterpTo(currentLocation, DesiredLocation, DeltaTime, 10.0f);
		FRotator NewRotation = FMath::RInterpTo(currentRotation, DesiredRotation, DeltaTime, 10.0f);
		GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation);

		if (NewLocation.Equals(DesiredLocation, 0.1f) && NewRotation.Equals(DesiredRotation, 0.1f))
		{
			bMoveToDesiredTransform = false;
		}
	}
}

void UMovementController::TurnLeft(const FInputActionInstance& Instance)
{
	if (IsAtTable and TableCameraTiltDirection > -1)
	{
		if (TableCameraTiltDirection == 1)
		{
			DesiredRotation -= TableCameraTiltRotation;
		}
		else
		{
			DesiredRotation -= FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
		}
		TableCameraTiltDirection--;
	}
	else if (!IsAtTable)
	{
		DesiredRotation -= FRotator(0.0f, 90.0f, 0.0f);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::TurnRight(const FInputActionInstance& Instance)
{
	if (IsAtTable and TableCameraTiltDirection < 1)
	{
		if (TableCameraTiltDirection == -1)
		{
			DesiredRotation += FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
		}
		else
		{
			DesiredRotation += TableCameraTiltRotation;
		}
		TableCameraTiltDirection++;
	}
	else if (!IsAtTable)
	{
		DesiredRotation += FRotator(0.0f, 90.0f, 0.0f);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::MoveForward(const FInputActionInstance& Instance)
{
	if (!IsAtTable)
	{
		DesiredLocation += (DesiredRotation.Vector() * DistanceToMove);

		if (DesiredLocation.Equals(TableLocation, 0.1f) and DesiredRotation.Equals(TableRotation, 0.1f))
		{
			IsAtTable = true;
			DesiredLocation += TableCameraTranslation;
			DesiredRotation -= TableCameraDownRotation;
			AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
			GameCharacter->ShowCardOverlay();
		}
		bMoveToDesiredTransform = true;
	}
}

void UMovementController::MoveBackward(const FInputActionInstance& Instance)
{
	if (IsAtTable and TableCameraTiltDirection != 0)
	{
		DesiredRotation -= FRotator(TableCameraTiltRotation.Pitch, TableCameraTiltDirection * TableCameraTiltRotation.Yaw, TableCameraTiltDirection * TableCameraTiltRotation.Roll);
		TableCameraTiltDirection = 0;
	}
	else if (IsAtTable and TableCameraTiltDirection == 0)
	{
		IsAtTable = false;
		DesiredLocation -= TableCameraTranslation;
		DesiredRotation += TableCameraDownRotation;
		AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
		GameCharacter->HideCardOverlay();
	}
	if (!IsAtTable) {
		DesiredLocation -= (DesiredRotation.Vector() * DistanceToMove);
	}
	bMoveToDesiredTransform = true;
}
