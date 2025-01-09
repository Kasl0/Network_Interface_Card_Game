#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialoguesProgressManager.generated.h"

/**
 * 
 */
UCLASS()
class NICGAME_API UDialoguesProgressManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	bool IsFirstIntroductionCompleted = false;
	bool IsSecondIntroductionCompleted = false;
	bool IsFirstGameCompleted = false;
	bool IsSecondGameCompleted = false;

public:

	UFUNCTION(BlueprintCallable)
	bool GetIsFirstIntroductionCompleted();

	UFUNCTION(BlueprintCallable)
	bool GetIsSecondIntroductionCompleted();

	UFUNCTION(BlueprintCallable)
	bool GetIsFirstGameCompleted();

	UFUNCTION(BlueprintCallable)
	bool GetIsSecondGameCompleted();

	UFUNCTION(BlueprintCallable)
	void SetIsFirstIntroductionCompleted();

	UFUNCTION(BlueprintCallable)
	void SetIsSecondIntroductionCompleted();

	UFUNCTION(BlueprintCallable)
	void SetIsFirstGameCompleted();

	UFUNCTION(BlueprintCallable)
	void SetIsSecondGameCompleted();
};
