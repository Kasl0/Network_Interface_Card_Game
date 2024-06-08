#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MovementController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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

	// Movement controller
	UPROPERTY(EditAnywhere)
	UMovementController* MovementController;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Show card overlay
	UFUNCTION(BlueprintImplementableEvent)
	void ShowCardOverlay();

	// Hide card overlay
	UFUNCTION(BlueprintImplementableEvent)
	void HideCardOverlay();
};
