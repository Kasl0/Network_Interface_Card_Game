// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckInfo.h"

#include "Cards/CardData.h"
#include "Cards/Minion.h"
#include "Cards/Spell.h"
#include "Cards/Effects/MinionModiferEffect.h"

void UDeckInfo::CreateMockDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		// Hard-coded for now
		UMinion* Minion1 = NewObject<UMinion>();
		Minion1->Init(1, "Example 1", "Example 1", 1, 2);
		Minion1->AddToRoot();
		this->SinglePlayerDeck.Add(Minion1);

		UMinion* Minion2 = NewObject<UMinion>();
		Minion2->Init(1, "Example 2", "Example 2", 2, 1);
		Minion2->AddToRoot();
		this->SinglePlayerDeck.Add(Minion2);

		UMinion* Minion3 = NewObject<UMinion>();
		Minion3->Init(2, "Example 3", "Example 3", 2, 4);
		Minion3->AddToRoot();
		this->SinglePlayerDeck.Add(Minion3);

		UMinion* Minion4 = NewObject<UMinion>();
		Minion4->Init(2, "Example 4", "Example 4", 3, 4);
		Minion4->AddToRoot();
		this->SinglePlayerDeck.Add(Minion4);

		UMinion* Minion5 = NewObject<UMinion>();
		Minion5->Init(3, "Example 5", "Example 5", 6, 6);
		Minion5->AddToRoot();
		this->SinglePlayerDeck.Add(Minion5);

		USpell* Spell1 = NewObject<USpell>();
		Spell1->SetData(1, "Example spell 1", "Give a minion +1/+1");
		UMinionModiferEffect* Effect = NewObject<UMinionModiferEffect>();
		UMinionModifier* Modifier = NewObject<UMinionModifier>();
		Modifier->AttackModifier = 1;
		Modifier->HealthModifier = 1;
		Effect->Init(Modifier);
		Spell1->init(Effect);
		Spell1->AddToRoot();
		this->SinglePlayerDeck.Add(Spell1);
	}
}

TArray<UCardData*> UDeckInfo::GetSinglePlayerDeck()
{
	if (this->SinglePlayerDeck.Num() == 0)
	{
		this->CreateMockDeck();
	}

	for (int i = 0; i < this->SinglePlayerDeck.Num(); i++)
	{
		this->DeckCopy.Add(DuplicateObject(this->SinglePlayerDeck[i], this->GetOuter()));
	}
	return DeckCopy;
}