#include "Player/MovementController.h"
#include "Player/GameCharacter.h"
#include "Player/TableCameraTiltDirection.h"

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
	TableCameraTiltDirection = TableCameraTiltDirection::None;
	TableCameraTiltRotation = FRotator(15.0f, 30.0f, 0.0f);
	TableCameraForwardTiltTranslation = FVector(-30.0f, 0.0f, 5.0f);
	IsIgnoringInput = false;
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
	if (IsIgnoringInput)
	{
		return;
	}
	if (IsAtTable)
	{
		if (TableCameraTiltDirection == TableCameraTiltDirection::Right)
		{
			DesiredRotation -= TableCameraTiltRotation;
			TableCameraTiltDirection = TableCameraTiltDirection::None;
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::None)
		{
			DesiredRotation -= FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
			TableCameraTiltDirection = TableCameraTiltDirection::Left;
		}
	}
	else
	{
		DesiredRotation -= FRotator(0.0f, 90.0f, 0.0f);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::TurnRight(const FInputActionInstance& Instance)
{
	if (IsIgnoringInput)
	{
		return;
	}
	if (IsAtTable)
	{
		if (TableCameraTiltDirection == TableCameraTiltDirection::Left)
		{
			DesiredRotation += FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
			TableCameraTiltDirection = TableCameraTiltDirection::None;
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::None)
		{
			DesiredRotation += TableCameraTiltRotation;
			TableCameraTiltDirection = TableCameraTiltDirection::Right;
		}
	}
	else
	{
		DesiredRotation += FRotator(0.0f, 90.0f, 0.0f);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::MoveForward(const FInputActionInstance& Instance)
{
	if (IsIgnoringInput)
	{
		return;
	}
	if (IsAtTable)
	{
		if (TableCameraTiltDirection == TableCameraTiltDirection::None)
		{
			DesiredRotation -= (FRotator(90.0f, 0.0f, 0.0f) - TableCameraDownRotation);
			DesiredLocation += TableCameraForwardTiltTranslation;
			TableCameraTiltDirection = TableCameraTiltDirection::Forward;
		}
	}
	else
	{
		if (DesiredLocation.Equals(TableLocation, 0.1f) and DesiredRotation.Equals(TableRotation, 0.1f))
		{
			IsAtTable = true;
			DesiredLocation += TableCameraTranslation;
			DesiredRotation -= TableCameraDownRotation;
			
			// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
			// GameCharacter->ShowCardOverlay();
			this->GamePhaseSubsystem->ChangeOverlay(1);
		}
		else
		{
			DesiredLocation += (DesiredRotation.Vector() * DistanceToMove);
		}	
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::MoveBackward(const FInputActionInstance& Instance)
{
	if (IsIgnoringInput)
	{
		return;
	}
	if (IsAtTable)
	{
		if (TableCameraTiltDirection == TableCameraTiltDirection::Left)
		{
			DesiredRotation += FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
			TableCameraTiltDirection = TableCameraTiltDirection::None;
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::Right)
		{
			DesiredRotation -= TableCameraTiltRotation;
			TableCameraTiltDirection = TableCameraTiltDirection::None;
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::Forward)
		{
			DesiredRotation += (FRotator(90.0f, 0.0f, 0.0f) - TableCameraDownRotation);
			DesiredLocation -= TableCameraForwardTiltTranslation;
			TableCameraTiltDirection = TableCameraTiltDirection::None;
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::None)
		{
			IsAtTable = false;
			DesiredLocation -= TableCameraTranslation;
			DesiredRotation += TableCameraDownRotation;
			// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
			// GameCharacter->HideCardOverlay();
			this->GamePhaseSubsystem->ChangeOverlay(0);
		}
	}
	else
	{
		DesiredLocation -= (DesiredRotation.Vector() * DistanceToMove);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::SetView(enum TableCameraTiltDirection Location, bool IgnoreInput)
{
	switch (Location)
	{
		case TableCameraTiltDirection::None:
			DesiredRotation = TableRotation - TableCameraDownRotation;
			DesiredLocation = TableLocation + TableCameraTranslation;
			break;
		case TableCameraTiltDirection::Forward:
			DesiredRotation = TableRotation - FRotator(90.0f, 0.0f, 0.0f);
			DesiredLocation = TableLocation + TableCameraTranslation + TableCameraForwardTiltTranslation;
			break;
		case TableCameraTiltDirection::Left:
			DesiredRotation = TableRotation - TableCameraDownRotation - FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
			DesiredLocation = TableLocation + TableCameraTranslation;
			break;
		case TableCameraTiltDirection::Right:
			DesiredRotation = TableRotation + TableCameraTiltRotation;
			DesiredLocation = TableLocation + TableCameraTranslation;
			break;
	}
	IsIgnoringInput = IgnoreInput;
	IsAtTable = true;
	TableCameraTiltDirection = Location;
	bMoveToDesiredTransform = true;
	
	// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
	// GameCharacter->ShowCardOverlay();
	this->GamePhaseSubsystem->ChangeOverlay(1);
}

void UMovementController::SetGamePhaseSubsystem(UGamePhaseSubsystem* Subsystem)
{
	this->GamePhaseSubsystem = Subsystem;
}
