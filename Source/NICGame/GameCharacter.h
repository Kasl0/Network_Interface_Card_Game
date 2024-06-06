#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MovementController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "CardWidget.h"
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

	// Selected card
	UPROPERTY(EditAnywhere, Category = "Card")
	UCardWidget* SelectedCard;

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

	// Get selected card
	UFUNCTION(BlueprintCallable)
	UCardWidget* GetSelectedCard() const { return SelectedCard; }

	// Set selected card
	UFUNCTION(BlueprintCallable)
	void SetSelectedCard(UCardWidget* NewSelectedCard) { SelectedCard = NewSelectedCard; }
};
