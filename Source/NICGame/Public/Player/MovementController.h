#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "GamePhase/GamePhaseSubsystem.h"
#include "Player/TableCameraTiltDirection.h"
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

	// Whether to ignore the input
	bool IsIgnoringInput;

	// Camera movement when sitting down
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FVector TableCameraTranslation;

	// Table camera down rotation value
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FRotator TableCameraDownRotation;

	// Table camera tilt direction
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	TEnumAsByte<TableCameraTiltDirection> TableCameraTiltDirection;

	// Table camera tilt rotation value
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FRotator TableCameraTiltRotation;

	// Table camera forward tilt translation value
	UPROPERTY(EditAnywhere, Category = "TableCamera")
	FVector TableCameraForwardTiltTranslation;

	// Used to show/hide overlay
	UPROPERTY(BlueprintReadOnly)
	UGamePhaseSubsystem* GamePhaseSubsystem;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Movement
	void TurnLeft(const FInputActionInstance& Instance);
	void TurnRight(const FInputActionInstance& Instance);
	void MoveForward(const FInputActionInstance& Instance);
	void MoveBackward(const FInputActionInstance& Instance);
	
	// Move to the desired transform
	void SetView(enum TableCameraTiltDirection Location, bool IgnoreInput);

	UFUNCTION(BlueprintCallable)
	void SetGamePhaseSubsystem(UGamePhaseSubsystem* Subsystem);
};
