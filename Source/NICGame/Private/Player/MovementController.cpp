#include "Player/MovementController.h"
#include "Player/GameCharacter.h"
#include "Player/TableCameraTiltDirection.h"
#include "Dialogues/DialogueManager.h"
#include "Dialogues/DialoguesProgressManager.h"

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
	TableCameraDownRotation = FRotator(47.0f, 0.0f, 0.0f);
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

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
	if (!DialoguesProgressManager->GetIsFirstIntroductionCompleted())
	{
		IsIgnoringInput = true;

		UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
		DialogueManager->CreateDialogueChain(1000, [this]() {

			SetView(TableCameraTiltDirection::None);
			UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
			UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
			UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
			DialoguesProgressManager->SetIsFirstIntroductionCompleted();
			DialogueManager->CreateDialogueChain(1100, [this]() {

				UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
				UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
				DialoguesProgressManager->SetIsSecondIntroductionCompleted();
				});
		});
	}
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
			/*DesiredRotation -= (FRotator(90.0f, 0.0f, 0.0f) - TableCameraDownRotation);
			DesiredLocation += TableCameraForwardTiltTranslation;
			TableCameraTiltDirection = TableCameraTiltDirection::Forward;*/
		}
	}
	else
	{
		if (DesiredLocation.Equals(TableLocation, 0.1f) and DesiredRotation.Equals(TableRotation, 0.1f))
		{
			UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
			UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
			if (!DialoguesProgressManager->GetIsTaskCompleted())
			{
				UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
				if (DialoguesProgressManager->GetIsWhiteCablePickedUp() && !DialoguesProgressManager->GetIsBlueCablePickedUp())
				{
					IsIgnoringInput = true;
					bPickedUpWrondCable = true;
					DialogueManager->CreateDialogueChain(1205, [this]() {
						UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
						UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
						DialogueManager->CreateDialogueChain(1207, [this]() {
							IsIgnoringInput = false;
							});
						});
					return;
				}
				else if (!DialoguesProgressManager->GetIsWhiteCablePickedUp() && DialoguesProgressManager->GetIsBlueCablePickedUp())
				{
					IsIgnoringInput = true;
					bPickedUpWrondCable = true;
					DialogueManager->CreateDialogueChain(1205, [this]() {
						UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
						UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
						DialogueManager->CreateDialogueChain(1206, [this]() {
							IsIgnoringInput = false;
							});
						});
					return;
				}
				else if (DialoguesProgressManager->GetIsWhiteCablePickedUp() && DialoguesProgressManager->GetIsBlueCablePickedUp())
				{
					IsIgnoringInput = true;
					if (bPickedUpWrondCable)
					{
						DialogueManager->CreateDialogueChain(1208, [this]() {
							IsIgnoringInput = false;
							UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
							UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
							DialoguesProgressManager->SetIsTaskCompleted();
							});
					}
					else
					{
						DialogueManager->CreateDialogueChain(1209, [this]() {
							IsIgnoringInput = false;
							UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
							UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
							DialoguesProgressManager->SetIsTaskCompleted();
							});
					}
				}
				else
				{
					return;
				}
			}

			IsAtTable = true;
			DesiredLocation += TableCameraTranslation;
			DesiredRotation -= TableCameraDownRotation;
			
			// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
			// GameCharacter->ShowCardOverlay();
			this->GamePhaseSubsystem->ChangeOverlay(1);
			this->GamePhaseSubsystem->ScreenWidgetComponent->RenderOnScreen();
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
			/*DesiredRotation += (FRotator(90.0f, 0.0f, 0.0f) - TableCameraDownRotation);
			DesiredLocation -= TableCameraForwardTiltTranslation;
			TableCameraTiltDirection = TableCameraTiltDirection::None;*/
		}
		else if (TableCameraTiltDirection == TableCameraTiltDirection::None)
		{
			IsAtTable = false;
			DesiredLocation -= TableCameraTranslation;
			DesiredRotation += TableCameraDownRotation;
			// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
			// GameCharacter->HideCardOverlay();
			this->GamePhaseSubsystem->ChangeOverlay(0);
			this->GamePhaseSubsystem->ScreenWidgetComponent->RenderInWorld();

			UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
			UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
			if (!DialoguesProgressManager->GetWasTaskOrdered())
			{
				UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
				DialogueManager->CreateDialogueChain(1202, [this]() {

					UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
					UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
					UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
					DialoguesProgressManager->SetWasTaskOrdered();
					});
			}
		}
	}
	else
	{
		DesiredLocation -= (DesiredRotation.Vector() * DistanceToMove);
	}
	bMoveToDesiredTransform = true;
}

void UMovementController::SetView(enum TableCameraTiltDirection Location)
{
	switch (Location)
	{
	case TableCameraTiltDirection::None:
		DesiredRotation = TableRotation - TableCameraDownRotation;
		DesiredLocation = TableLocation + TableCameraTranslation;
		break;
		/*case TableCameraTiltDirection::Forward:
			DesiredRotation = TableRotation - FRotator(90.0f, 0.0f, 0.0f);
			DesiredLocation = TableLocation + TableCameraTranslation + TableCameraForwardTiltTranslation;
			break;*/
	case TableCameraTiltDirection::Left:
		DesiredRotation = TableRotation - TableCameraDownRotation - FRotator(-TableCameraTiltRotation.Pitch, TableCameraTiltRotation.Yaw, TableCameraTiltRotation.Roll);
		DesiredLocation = TableLocation + TableCameraTranslation;
		break;
	case TableCameraTiltDirection::Right:
		DesiredRotation = TableRotation + TableCameraTiltRotation;
		DesiredLocation = TableLocation + TableCameraTranslation;
		break;
	}
	IsAtTable = true;
	TableCameraTiltDirection = Location;
	bMoveToDesiredTransform = true;

	// AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetOwner());
	// GameCharacter->ShowCardOverlay();
	this->GamePhaseSubsystem->ChangeOverlay(1);
	this->GamePhaseSubsystem->ScreenWidgetComponent->RenderOnScreen();
}

void UMovementController::SetIgnoreInput(bool IgnoreInput)
{
	IsIgnoringInput = IgnoreInput;
}

void UMovementController::SetGamePhaseSubsystem(UGamePhaseSubsystem* Subsystem)
{
	this->GamePhaseSubsystem = Subsystem;
}
