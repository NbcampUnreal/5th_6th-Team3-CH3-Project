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
class UEnemyHitState;

UCLASS()
class PROJECTSOUL_API UEnemyStateMachine : public UStateMachineBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacter* InOwner) override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void ChangeState(UStateBase* NewState) override;

	UEnemyStateBase* GetCurrentState() const;

	UEnemyChaseState* GetChaseState() const;

	UEnemyAttackState* GetAttackState() const;

	UEnemyDieState* GetDieState() const;

	UEnemyIdleState* GetIdleState() const;

	UEnemyInvestigateState* GetInvestigateState() const;

	UEnemyReturnState* GetReturnState() const;

	UEnemyHitState* GetHitState() const;

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

	UPROPERTY()
	TObjectPtr <UEnemyHitState> HitState;
};
