#include "Deck/EnemyDeckInfo.h"
#include "Cards/CardTypes/CardData.h"
#include "Cards/CardService.h"
#include "Kismet/GameplayStatics.h"

UCardData* UEnemyDeckInfo::GetCard()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UCardService* CardServ = Cast<UCardService>(GameInstance->GetSubsystem<UCardService>());

	// here we need to get a current layer info
	// for now we will just pass -1 which means random card from all layers

	UCardData* Card = CardServ->GetRandomEnemyCard(-1);

	Card->AddToRoot();
	UCardData* CardCopy = DuplicateObject(Card, this->GetOuter());

	return CardCopy;
}
