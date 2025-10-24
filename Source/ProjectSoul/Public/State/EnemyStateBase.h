#pragma once

#include "CoreMinimal.h"
#include "State/StateBase.h"
#include "EnemyStateBase.generated.h"

class UEnemyStateMachine;
class APSEnemy;

UCLASS()
class PROJECTSOUL_API UEnemyStateBase : public UStateBase
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

protected:
	UEnemyStateMachine* GetEnemyStateMachine() const;

	APSEnemy* GetEnemyCharacter() const;
};
