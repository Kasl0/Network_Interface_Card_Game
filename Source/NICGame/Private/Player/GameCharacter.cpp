#include "Player/GameCharacter.h"

#include "GamePhase/GamePhaseSubsystem.h"
#include "Player/MovementController.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create components
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MovementController = CreateDefaultSubobject<UMovementController>(TEXT("MovementController"));
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = this->GetWorld()->GetGameInstance();
	if (GameInstance)
	{
		UGamePhaseSubsystem* GamePhaseSubsystem = GameInstance->GetSubsystem<UGamePhaseSubsystem>();
		this->MovementController->SetGamePhaseSubsystem(GamePhaseSubsystem);
	}
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
			Input->BindAction(TurnLeftAction, ETriggerEvent::Triggered, MovementController, &UMovementController::TurnLeft);
		}
		if (TurnRightAction)
		{
			Input->BindAction(TurnRightAction, ETriggerEvent::Triggered, MovementController, &UMovementController::TurnRight);
		}
		if (MoveForwardAction)
		{
			Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, MovementController, &UMovementController::MoveForward);
		}
		if (MoveBackwardAction)
		{
			Input->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, MovementController, &UMovementController::MoveBackward);
		}
	}
}

void AGameCharacter::SetView(enum TableCameraTiltDirection Location)
{
	MovementController->SetView(Location);
}

void AGameCharacter::SetIgnoreInput(bool IgnoreInput)
{
	MovementController->SetIgnoreInput(IgnoreInput);
}
