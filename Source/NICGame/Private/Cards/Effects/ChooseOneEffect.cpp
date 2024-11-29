// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Effects/ChooseOneEffect.h"
#include "Cards/CardTypes/Spell.h"
#include "Cards/Effects/DrawEffect.h"
#include "Cards/Effects/SummonEffect.h"
#include "Cards/Effects/ShuffleIntoDeckEffect.h"
#include "Cards/Effects/MinionModifiers/StatModifier.h"
#include "Deck/BattleDeck.h"
#include "Cards/CardHand.h"
#include "Duel/DuelState.h"
#include "Duel/DuelCharacter.h"
#include "Cards/CreateCardChoice.h"

void UChooseOneEffect::Init(CardService* CardService, int32 id1, int32 id2, int32 id3)
{
	this->World = CardService->GetWorld();

	for (int32 id : {id1, id2, id3})
	{
		UCardData* Card = CardService->GetCardData(id);
		if (Card)
		{
			Card->AddToRoot();
			this->Cards.Add(Card);
		}
	}
}

void UChooseOneEffect::Apply(UObject* EffectTarget, TFunction<void()> AfterChoiceCallback)
{
	UCreateCardChoice* Choice = NewObject<UCreateCardChoice>();
	auto Callback = [this, EffectTarget, AfterChoiceCallback](UCardData* CardChosen) {
		USpell* Spell = Cast<USpell>(CardChosen);
		if (Spell)
		{
			UEffect* Effect = Spell->SpellEffect;
			if (Cast<UDrawEffect>(Effect))
			{
				UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
				UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
				UDuelCharacter* Character = DuelState->GetCharacters()[Friendly];
				Effect->Apply(Character);
			} 
			else if (Cast<UStatModifier>(Effect))
			{
				Effect->Apply(EffectTarget); // Target should be calling minion
			}
			else if (USummonEffect* SummonEffect = Cast<USummonEffect>(Effect))
			{
				SummonEffect->ApplySummonEffect(Friendly); // I assume only player calls this
			}
			else if (UShuffleIntoDeckEffect* ShuffleEffect = Cast<UShuffleIntoDeckEffect>(Effect))
			{
				UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
				UBattleDeck* Deck = Cast<UBattleDeck>(GameInstance->GetSubsystem<UBattleDeck>());
				ShuffleEffect->ApplyShuffle(Deck);
			}
			// If other effect, do nothing
			// Add new ifs in case of new cards that need it

			if (AfterChoiceCallback) AfterChoiceCallback();
		}
	};
	Choice->CreateChoice(Cards, Callback, this->World);
}
