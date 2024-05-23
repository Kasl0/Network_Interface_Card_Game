#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "MovementController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NICGAME_API UMovementController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Whether to move to the desired transform
	bool bMoveToDesiredTransform;

	// Desired transform
	FVector DesiredLocation;
	FRotator DesiredRotation;

	// Forward/backward movement distance
	UPROPERTY(EditAnywhere, Category = "Moving")
	float DistanceToMove;

	// Table location vector
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FVector TableLocation;

	// Whether the player is at the table
	bool IsAtTable;

	// Table camera down rotation value
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FRotator TableCameraDownRotation;

	// Table camera tilt direction:
	// -1: left
	//	0: none
	//	1: right
	int TableCameraTiltDirection;

	// Table camera tilt rotation value
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FRotator TableCameraTiltRotation;

	// Show card overlay
	UFUNCTION(BlueprintImplementableEvent)
	void ShowCardOverlay();

	// Hide card overlay
	UFUNCTION(BlueprintImplementableEvent)
	void HideCardOverlay();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Movement
	void TurnLeft(const FInputActionInstance& Instance);
	void TurnRight(const FInputActionInstance& Instance);
	void MoveForward(const FInputActionInstance& Instance);
	void MoveBackward(const FInputActionInstance& Instance);
};
