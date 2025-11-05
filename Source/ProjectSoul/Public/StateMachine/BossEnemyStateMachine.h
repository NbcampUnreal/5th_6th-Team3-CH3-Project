#pragma once

#include "CoreMinimal.h"
#include "StateMachine/StateMachineBase.h"
#include "BossEnemyStateMachine.generated.h"

class UEnemyStateBase;
class UEnemyChaseState;
class UBossEnemyAttackState;
class UBossEnemySkillAttackState;
class UEnemyDieState;
class UEnemyIdleState;
class UEnemyInvestigateState;
class UEnemyReturnState;
class UBossEnemyHitState;

UCLASS()
class PROJECTSOUL_API UBossEnemyStateMachine : public UStateMachineBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacter* InOwner) override;

	virtual void OnUpdate(float DeltaTime) override;

	UEnemyStateBase* GetCurrentState() const;

	UEnemyChaseState* GetChaseState() const;

	UBossEnemyAttackState* GetBossAttackState() const;

	UBossEnemySkillAttackState* GetBossSkillAttackState() const;

	UEnemyDieState* GetDieState() const;

	UEnemyIdleState* GetIdleState() const;

	UEnemyInvestigateState* GetInvestigateState() const;

	UEnemyReturnState* GetReturnState() const;

	UBossEnemyHitState* GetHitState() const;

protected:
	UPROPERTY()
	TObjectPtr<UEnemyChaseState> ChaseState;

	UPROPERTY()
	TObjectPtr <UBossEnemyAttackState> BossAttackState;

	UPROPERTY()
	TObjectPtr <UBossEnemySkillAttackState> BossSkillAttackState;

	UPROPERTY()
	TObjectPtr<UEnemyDieState> DieState;

	UPROPERTY()
	TObjectPtr <UEnemyIdleState> IdleState;

	UPROPERTY()
	TObjectPtr<UEnemyInvestigateState> InvestigateState;

	UPROPERTY()
	TObjectPtr <UEnemyReturnState> ReturnState;

	UPROPERTY()
	TObjectPtr <UBossEnemyHitState> HitState;
};
