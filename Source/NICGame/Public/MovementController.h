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
	UPROPERTY(EditAnywhere, Category = "Moving")
	bool bMoveToDesiredTransform;

	// Desired transform
	UPROPERTY(EditAnywhere, Category = "Moving")
	FVector DesiredLocation;
	UPROPERTY(EditAnywhere, Category = "Moving")
	FRotator DesiredRotation;

	// Forward/backward movement distance
	UPROPERTY(EditAnywhere, Category = "Moving")
	float DistanceToMove;

	// Table transform
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FVector TableLocation;
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FRotator TableRotation;

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Movement
	void TurnLeft(const FInputActionInstance& Instance);
	void TurnRight(const FInputActionInstance& Instance);
	void MoveForward(const FInputActionInstance& Instance);
	void MoveBackward(const FInputActionInstance& Instance);
};
