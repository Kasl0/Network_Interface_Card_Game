#include "MovementController.h"

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
	IsAtTable = false;
	TableCameraDownRotation = FRotator(40.0f, 0.0f, 0.0f);
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
	FRotator newRotation = GetOwner()->GetActorRotation();
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
	GetOwner()->SetActorRotation(newRotation);
}

void UMovementController::TurnRight(const FInputActionInstance& Instance)
{
	FRotator newRotation = GetOwner()->GetActorRotation();
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
	GetOwner()->SetActorRotation(newRotation);
}

void UMovementController::MoveForward(const FInputActionInstance& Instance)
{
	if (!IsAtTable)
	{
		AActor* Owner = GetOwner();
		FVector newLocation = Owner->GetActorLocation();
		FVector forwardVector = Owner->GetActorForwardVector();
		newLocation += (forwardVector * DistanceToMove);

		if (newLocation.Equals(TableLocation) and Owner->GetActorRotation().Equals(FRotator(0.0f, 180.0f, 0.0f), 0.1f))
		{
			IsAtTable = true;
			FRotator newRotation = Owner->GetActorRotation();
			newRotation -= TableCameraDownRotation;
			DesiredRotation = newRotation;
			this->ShowCardOverlay();
		}
		DesiredLocation = newLocation;
		bMoveToDesiredTransform = true;
	}
}

void UMovementController::MoveBackward(const FInputActionInstance& Instance)
{
	if (IsAtTable and TableCameraTiltDirection != 0)
	{
		FRotator newRotation = GetOwner()->GetActorRotation();
		newRotation -= FRotator(TableCameraTiltRotation.Pitch, TableCameraTiltDirection * TableCameraTiltRotation.Yaw, TableCameraTiltDirection * TableCameraTiltRotation.Roll);
		GetOwner()->SetActorRotation(newRotation);
		TableCameraTiltDirection = 0;
	}
	else if (IsAtTable and TableCameraTiltDirection == 0)
	{
		FRotator newRotation = GetOwner()->GetActorRotation();
		newRotation += TableCameraDownRotation;
		GetOwner()->SetActorRotation(newRotation);
		IsAtTable = false;
		this->HideCardOverlay();
	}
	if (!IsAtTable) {
		FVector newLocation = GetOwner()->GetActorLocation();
		FVector forwardVector = GetOwner()->GetActorForwardVector();
		newLocation -= (forwardVector * DistanceToMove);
		GetOwner()->SetActorLocation(newLocation);
	}
}
