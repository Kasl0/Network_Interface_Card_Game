#include "Dialogues/DialoguesProgressManager.h"

bool UDialoguesProgressManager::GetIsFirstIntroductionCompleted()
{
	return IsFirstIntroductionCompleted;
}

bool UDialoguesProgressManager::GetIsSecondIntroductionCompleted()
{
	return IsSecondIntroductionCompleted;
}

bool UDialoguesProgressManager::GetIsFirstGameCompleted()
{
	return IsFirstGameCompleted;
}

bool UDialoguesProgressManager::GetWasTaskOrdered()
{
	return WasTaskOrdered;
}

bool UDialoguesProgressManager::GetIsBlueCablePickedUp()
{
	return IsBlueCablePickedUp;
}

bool UDialoguesProgressManager::GetIsWhiteCablePickedUp()
{
	return IsWhiteCablePickedUp;
}

bool UDialoguesProgressManager::GetIsTaskCompleted()
{
	return IsTaskCompleted;
}

bool UDialoguesProgressManager::GetIsSecondGameCompleted()
{
	return IsSecondGameCompleted;
}

void UDialoguesProgressManager::SetIsFirstIntroductionCompleted()
{
	IsFirstIntroductionCompleted = true;
}

void UDialoguesProgressManager::SetIsSecondIntroductionCompleted()
{
	IsSecondIntroductionCompleted = true;
}

void UDialoguesProgressManager::SetIsFirstGameCompleted()
{
	IsFirstGameCompleted = true;
}

void UDialoguesProgressManager::SetWasTaskOrdered()
{
	WasTaskOrdered = true;
}

void UDialoguesProgressManager::SetIsBlueCablePickedUp()
{
	IsBlueCablePickedUp = true;
}

void UDialoguesProgressManager::SetIsWhiteCablePickedUp()
{
	IsWhiteCablePickedUp = true;
}

void UDialoguesProgressManager::SetIsTaskCompleted()
{
	IsTaskCompleted = true;
}

void UDialoguesProgressManager::SetIsSecondGameCompleted()
{
	IsSecondGameCompleted = true;
}
