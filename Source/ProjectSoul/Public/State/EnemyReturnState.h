#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyReturnState.generated.h"

UCLASS()
class PROJECTSOUL_API UEnemyReturnState : public UEnemyStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnExit() override;
};
