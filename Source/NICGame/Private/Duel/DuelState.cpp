#include "Duel/DuelState.h"
#include "Cards/CardWidget.h"
#include "Duel/EnemyDuelCharacter.h"
#include "Duel/FriendlyDuelCharacter.h"
#include "Duel/Board/BoardState.h"
#include "Duel/DuelCharacter.h"
#include "Engine/Engine.h" // temporary for debug text
#include "Kismet/GameplayStatics.h"
#include "Player/GameCharacter.h"
#include "Deck/BattleDeck.h"
#include "Cards/CardHand.h"
#include "Cards/CardTypes/Spell.h"
#include "Cards/CardTypes/JadeGolemMinion.h"
#include "Duel/Board/BoardWidget.h"
#include "Dialogues/DialogueManager.h"
#include "Dialogues/DialoguesProgressManager.h"
#include "Player/MovementController.h"

//UDuelState::UDuelState()
//{
//	// Moved to StartDuel()
//	// this->BoardState->AddToRoot();
//}

void UDuelState::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	this->BoardState = NewObject<UBoardState>();
	this->BoardState->Init(this, 4, GetWorld());
}

bool UDuelState::IsDuelInProgress()
{
	return this->DuelCharacters.Num() > 0;
}

void UDuelState::StartDuel(EBoardSide StartingSide)
{
	// initialize deck
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UBattleDeck* BattleDeck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
	BattleDeck->InitializeDeck(GetWorld());

	// initialize card hand
	UCardHand* CardHand = Cast<UCardHand>(GameInstance->GetSubsystem<UCardHand>());
	CardHand->RemoveAllCardData();

	// Initialize jade golem stats
	UJadeGolemMinion::Stats = 1;

	this->BoardState->Init(this, 4, GetWorld());

	// initialize characters
	for (EBoardSide Side : {Friendly, Enemy})
	{
		if (this->DuelCharacters.Contains(Side))
		{
			this->DuelCharacters[Side]->RemoveFromRoot();
			this->DuelCharacters.Remove(Side);
		}

		if (Side == Enemy) {
			UEnemyDuelCharacter* Character0 = NewObject<UEnemyDuelCharacter>();
			Character0->Init();
			Character0->AddToRoot();
			UEnemyDuelCharacter* Character = DuplicateObject(Character0, this->GetOuter());
			Character->InitializeDuelState(this);
			this->DuelCharacters.Add(Side, Character);
		}
		else {
			UFriendlyDuelCharacter* Character0 = NewObject<UFriendlyDuelCharacter>();
			Character0->Init(GetWorld());
			Character0->AddToRoot();
			UFriendlyDuelCharacter* Character = DuplicateObject(Character0, this->GetOuter());
			this->DuelCharacters.Add(Side, Character);
		}
	}
	this->CurrentTurn = StartingSide;
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
}

UCardWidget* UDuelState::GetSelectedCard() const
{
	return this->CurrentTurn == Friendly ? SelectedCard : nullptr;
}

void UDuelState::SetSelectedCard(UCardWidget* NewSelectedCard)
{
	if (NewSelectedCard)
	{
		USpell* Spell = Cast<USpell>(NewSelectedCard->CardData);
		if (Spell && Spell->SpellEffect->Target == NoTarget)
		{
			if (PlayCard(Spell, 0))
			{
				UGameInstance* Ins = Cast<UGameInstance>(GetWorld()->GetGameInstance());
				UCardHand* CardHand = Cast<UCardHand>(Ins->GetSubsystem<UCardHand>());
				CardHand->RemoveCardData(Spell);
			}
		}
		else
		{
			this->SelectedCard = NewSelectedCard;
		}
	}
	else
	{
		this->SelectedCard = NewSelectedCard;
	}
}

void UDuelState::PrepareTurnEnd()
{
	if (this->CurrentTurn != None)
	{
		EndingTurn = this->CurrentTurn;
		this->CurrentTurn = None;
	}

	if (this->BoardWidget)
	{
		FTimerHandle TurnChangeHandle;
		if (this->BoardWidget->AreAnimationsFinished())
		{
			// if finished, proceed to minion attack
			this->BoardWidget->GetWorld()->GetTimerManager().SetTimer(
				TurnChangeHandle,
				this,
				&UDuelState::EndPlayerTurn,
				0.5f,
				false
			);
		}
		else 
		{
			// if not finished, wait
			this->BoardWidget->GetWorld()->GetTimerManager().SetTimer(
				TurnChangeHandle,
				this,
				&UDuelState::PrepareTurnEnd,
				0.1f,
				false
			);
		}
	}
}

void UDuelState::EndPlayerTurn()
{
	this->DuelCharacters[TEnumAsByte(EndingTurn)]->EndTurn();

	this->BoardState->MinionAttack(EndingTurn, [this]() { this->SwitchPlayerTurn(); });
}

void UDuelState::SwitchPlayerTurn()
{
	AGameCharacter* Player = Cast<AGameCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->SetView(TableCameraTiltDirection::None, false);

	this->CurrentTurn = EndingTurn == Friendly ? Enemy : Friendly;
	if (this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->CheckDeath())
	{
		return;
	}

	auto SwitchTurnLambda = [this] { this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn(); };
	FTimerDelegate SwitchTurnDelegate;
	SwitchTurnDelegate.BindLambda(SwitchTurnLambda);

	FTimerHandle SwitchTimer;
	GetWorld()->GetTimerManager().SetTimer(
		SwitchTimer,
		SwitchTurnDelegate,
		0.5f,
		false
	);
}

TMap<TEnumAsByte<EBoardSide>, UDuelCharacter*> UDuelState::GetCharacters()
{
	return this->DuelCharacters;
}

bool UDuelState::PlayCard(UCardData* CardData, uint8 Column)
{
	if (this->DuelCharacters[TEnumAsByte(Friendly)]->UseMana(CardData->CardCost))
	{
		if (this->BoardState->PlaceCard(CardData, this->CurrentTurn, Column))
		{
			return true;
		}
		else
		{
			this->DuelCharacters[TEnumAsByte(Friendly)]->UseMana(-CardData->CardCost); // refund mana
			return false;
		}
	}
	else
	{
		return false;
	}
}

UBoardState* UDuelState::GetBoardState()
{
	return this->BoardState;
}

UEnemyDeckInfo* UDuelState::GetEnemyDeckInfo()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	return Cast<UEnemyDeckInfo>(GameInstance->GetSubsystem<UEnemyDeckInfo>());
}

void UDuelState::EndDuel(EBoardSide WinningSide, uint8 excessiveDamage)
{
	if (this->BoardWidget)
	{
		if (this->BoardWidget->AreAnimationsFinished())
		{
			// temporary debug text
			FString Text1 = "GAME OVER! Winner: ";
			Text1.Append(WinningSide == TEnumAsByte(Friendly) ? "Player" : "Enemy");
			Text1.Append(" with excessiveDamage = ");
			Text1.Append(FString::FromInt(excessiveDamage));

			if (GEngine) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Text1);
			}

			UGameInstance* GameInstance = this->GetWorld()->GetGameInstance();
			if (GameInstance)
			{
				UDialogueManager* DialogueManager = Cast<UDialogueManager>(GameInstance->GetSubsystem<UDialogueManager>());
				UDialoguesProgressManager* DialoguesProgressManager = Cast<UDialoguesProgressManager>(GameInstance->GetSubsystem<UDialoguesProgressManager>());
				if (!DialoguesProgressManager->GetIsFirstGameCompleted())
				{
					DialoguesProgressManager->SetIsFirstGameCompleted();
					//set ignoring input to false
					DialogueManager->CreateDialogueChain(1200, [this]() {});
				}
				UGamePhaseSubsystem* GamePhaseSubsystem = GameInstance->GetSubsystem<UGamePhaseSubsystem>();
				if (GamePhaseSubsystem)
				{
					GamePhaseSubsystem->MapPhase();
				}
			}
		}
		else
		{
			// if not finished, wait

			auto MyLambda = [this, WinningSide, excessiveDamage]()
				{
					this->EndDuel(WinningSide, excessiveDamage);
				};

			FTimerHandle Handle;
			this->BoardWidget->GetWorld()->GetTimerManager().SetTimer(
				Handle,
				MyLambda,
				0.1f,
				false
			);
		}
	}
}

EBoardSide UDuelState::GetCurrentTurn()
{
	return this->CurrentTurn;
}

UDuelCharacter* UDuelState::GetCurrentTurnCharacter()
{
	if (this->CurrentTurn == None)
	{
		return nullptr;
	}
	return this->DuelCharacters[TEnumAsByte(this->CurrentTurn)];
}

void UDuelState::SetBoardWidget(UBoardWidget* Widget)
{
	this->BoardWidget = Widget;
}

void UDuelState::DrawCardForFriendly()
{
	/*UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UCardHand* Hand = Cast<UCardHand>(GameInstance->GetSubsystem<UCardHand>());
	Hand->DrawCard();*/
}
