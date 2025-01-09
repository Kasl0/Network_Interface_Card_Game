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

void UDialoguesProgressManager::SetIsSecondGameCompleted()
{
	IsSecondGameCompleted = true;
}
