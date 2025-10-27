#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyHitState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyHitState : public UEnemyStateBase
{
	GENERATED_BODY()

	virtual void OnEnter() override;

	virtual void OnExit() override;
};
