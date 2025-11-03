#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyChaseState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyChaseState : public UEnemyStateBase
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;

	virtual void OnExit() override;
};
