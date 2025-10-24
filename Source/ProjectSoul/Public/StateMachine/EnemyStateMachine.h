#pragma once

#include "CoreMinimal.h"
#include "StateMachine/StateMachineBase.h"
#include "EnemyStateMachine.generated.h"

class UEnemyStateBase;
class UEnemyChaseState;
class UEnemyAttackState;
class UEnemyDieState;
class UEnemyIdleState;
class UEnemyInvestigateState;
class UEnemyReturnState;
class APSEnemy;

UCLASS()
class PROJECTSOUL_API UEnemyStateMachine : public UStateMachineBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacter* InOwner) override;

	virtual void OnUpdate(float DeltaTime) override;

	UEnemyStateBase* GetCurrentState() const;

	APSEnemy* GetOwnerEnemy() const;

	UEnemyChaseState* GetChaseState() const;

	UEnemyAttackState* GetAttackState() const;

	UEnemyDieState* GetDieState() const;

	UEnemyIdleState* GetIdleState() const;

	UEnemyInvestigateState* GetInvestigateStateState() const;

	UEnemyReturnState* GetReturnState() const;

protected:
	UPROPERTY()
	TObjectPtr<UEnemyChaseState> ChaseState;

	UPROPERTY()
	TObjectPtr <UEnemyAttackState> AttackState;

	UPROPERTY()
	TObjectPtr<UEnemyDieState> DieState;

	UPROPERTY()
	TObjectPtr <UEnemyIdleState> IdleState;

	UPROPERTY()
	TObjectPtr<UEnemyInvestigateState> InvestigateState;

	UPROPERTY()
	TObjectPtr <UEnemyReturnState> ReturnState;
};
