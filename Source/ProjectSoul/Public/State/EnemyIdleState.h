#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyIdleState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyIdleState : public UEnemyStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnExit() override;
};
