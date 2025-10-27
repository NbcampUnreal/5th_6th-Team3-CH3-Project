#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyDieState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyDieState : public UEnemyStateBase
{
	GENERATED_BODY()
	
	virtual void OnEnter() override;

	virtual void OnExit() override;

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	FOnMontageEnded EndDelegate;
};
