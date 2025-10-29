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

private:
	FOnMontageEnded EndDelegate;

	FTimerHandle DestroyTimerHandle;
};
