#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameCharacter.generated.h"

UCLASS()
class NICGAME_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	// Enhanced Input
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TurnLeftAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TurnRightAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* MoveBackwardAction;

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

	// Movement
	void TurnLeft(const FInputActionInstance& Instance);
	void TurnRight(const FInputActionInstance& Instance);
	void MoveForward(const FInputActionInstance& Instance);
	void MoveBackward(const FInputActionInstance& Instance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
