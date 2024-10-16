﻿#include "Duel/DuelState.h"
#include "Cards/CardWidget.h"
#include "Duel/EnemyDuelCharacter.h"
#include "Duel/Board/BoardState.h"
#include "Duel/DuelCharacter.h"
#include "Engine/Engine.h" // temporary for debug text
#include "Kismet/GameplayStatics.h"
#include "Player/GameCharacter.h"
#include "Deck/BattleDeck.h"
#include "Cards/CardHand.h"
#include "Duel/Board/BoardWidget.h"

UDuelState::UDuelState()
{
	this->BoardState = NewObject<UBoardState>();
	this->BoardState->Init(this, 4, GetWorld());
	// Moved to StartDuel()
	// this->BoardState->AddToRoot();
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
			UDuelCharacter* Character0 = NewObject<UDuelCharacter>();
			Character0->Init();
			Character0->AddToRoot();
			UDuelCharacter* Character = DuplicateObject(Character0, this->GetOuter());
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
	this->SelectedCard = NewSelectedCard;
}

void UDuelState::PrepareTurnEnd()
{
	FTimerHandle TurnChangeHandle;
	if (this->BoardWidget)
	{
		if (this->BoardWidget->AreAnimationsFinished())
		{
			// if finished, proceed to minion attack
			this->BoardWidget->GetWorld()->GetTimerManager().SetTimer(
				TurnChangeHandle,
				this,
				&UDuelState::EndPlayerTurn,
				0.1f,
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
	EBoardSide EndingTurn = this->CurrentTurn;
	this->CurrentTurn = None;

	this->DuelCharacters[TEnumAsByte(EndingTurn)]->EndTurn();

	this->BoardState->MinionAttack(EndingTurn, [this](EBoardSide EndingTurn) { this->SwitchPlayerTurn(EndingTurn); });
}

void UDuelState::SwitchPlayerTurn(EBoardSide EndingTurn)
{
	AGameCharacter* Player = Cast<AGameCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->SetView(TableCameraTiltDirection::None, false);
	
	this->CurrentTurn = EndingTurn == Friendly ? Enemy : Friendly;
	if (this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->CheckDeath())
	{
		return;
	}
	this->DuelCharacters[TEnumAsByte(this->CurrentTurn)]->StartTurn();
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
			//FString Text2 = "New game automatically started";

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Text1);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Text2);
			}

			UGameInstance* GameInstance = this->GetWorld()->GetGameInstance();
			if (GameInstance)
			{
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
