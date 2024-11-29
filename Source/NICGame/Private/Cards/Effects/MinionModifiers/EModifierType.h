#pragma once

UENUM()
enum EModifierType : uint8
{
	Base = 0, // No effect
	Stat = 1, // Change stats in some way
	BeforeAttack = 2, // Call an effect right before the minion attacks
	AfterAttack = 3, // Call an effect right after a minion attacks
	Status = 4, // Apply status (taunt or poison) to minion
	OnPlay =5, // Call an effect when this minion is played
	OnFriendlyMinionSummon = 6 // Call an effect when a friendly minion gets summoned
};
