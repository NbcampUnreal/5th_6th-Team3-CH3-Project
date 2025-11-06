#pragma once

#include "CoreMinimal.h"
#include "State/StateBase.h"
#include "EnemyStateBase.generated.h"

class UStateMachineBase;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UEnemyStateBase : public UStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

protected:
	UStateMachineBase* GetEnemyStateMachine() const;

	ACharacter* GetEnemyCharacter() const;
};
