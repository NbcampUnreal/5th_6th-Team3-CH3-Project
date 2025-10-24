#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyInvestigateState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyInvestigateState : public UEnemyStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnter() override;

	virtual void OnExit() override;
};
