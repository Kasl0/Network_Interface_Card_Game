#include "Duel/DuelCharacter.h"
#include "Duel/DuelState.h"

void UDuelCharacter::StartTurn()
{
	this->CurrentMana = this->BaseMana;
	this->CardDrawInCurrentTurn = 0;
}

void UDuelCharacter::EndTurn()
{
	this->CardDrawInCurrentTurn = 0;
}

void UDuelCharacter::Init(int32 Health, int32 Mana)
{
	this->BaseHealth = Health;
	this->CurrentHealth = this->BaseHealth;
	this->BaseMana = Mana;
}

void UDuelCharacter::TakeDamage(int32 DamageValue, UObject* Source)
{
	this->CurrentHealth -= DamageValue;
}

bool UDuelCharacter::CheckDeath()
{
	if (this->CurrentHealth <= 0)
	{
		UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
		UDuelState* DuelState = Cast<UDuelState>(GameInstance->GetSubsystem<UDuelState>());
		for (auto& Character : DuelState->GetCharacters())
		{
			if (Character.Value == this)
			{
				DuelState->EndDuel(Character.Key == Friendly ? Enemy : Friendly, this->CurrentHealth * -1);
				return true;
			}
		}
	}
	return false;
}

int32 UDuelCharacter::GetBaseMana() const
{
	return this->BaseMana;
}

int32 UDuelCharacter::GetCurrentMana() const
{
	return this->CurrentMana;
}

bool UDuelCharacter::UseMana(int32 Mana)
{
	if (Mana > this->CurrentMana)
	{
		return false;
	}
	else
	{
		this->CurrentMana -= Mana;
		return true;
	}
}

int32 UDuelCharacter::GetHealth()
{
	return this->CurrentHealth;
}

void UDuelCharacter::SetCardDrawInCurrentTurn(uint8 CardDraw)
{
	this->CardDrawInCurrentTurn = CardDraw;
}

uint8 UDuelCharacter::GetCardDrawInCurrentTurn()
{
	return this->CardDrawInCurrentTurn;
}
