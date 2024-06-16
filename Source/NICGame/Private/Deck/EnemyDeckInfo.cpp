#include "Deck/EnemyDeckInfo.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardTypes/Minion.h"
#include "Cards/CardTypes/Spell.h"
#include "Cards/Effects/MinionModiferEffect.h"

UCardData* UEnemyDeckInfo::GetCard()
{
	// One hard-coded enemy for now
	UMinion* Minion = NewObject<UMinion>();
	uint8 Cost = 1;
	std::string Name = "Enemy Minion";
	std::string Description = "Very strong enemy, OMG!";
	int32 Attack = FMath::RandRange(1, 3);
	int32 Health = FMath::RandRange(1, 3);
	Minion->Init(Cost, Name, Description, Attack, Health);
	Minion->AddToRoot();
	UCardData* Card = DuplicateObject(Minion, this->GetOuter());

	return Card;
}
