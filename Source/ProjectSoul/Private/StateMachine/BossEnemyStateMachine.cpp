#include "StateMachine/BossEnemyStateMachine.h"
#include "State/EnemyHitState.h"
#include "Enemy/PSBossEnemy.h"
#include "State/BossEnemyAttackState.h"
#include "State/BossEnemySkillAttackState.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyDieState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyInvestigateState.h"
#include "State/EnemyReturnState.h"

void UBossEnemyStateMachine::Initialize(ACharacter* InOwner)
{
	Super::Initialize(InOwner);

	IdleState = NewObject<UEnemyIdleState>(this);
	if (IdleState)
	{
		IdleState->Initialize(this);
	}

	BossAttackState = NewObject<UBossEnemyAttackState>(this);
	if (BossAttackState)
	{
		BossAttackState->Initialize(this);
	}

	BossSkillAttackState = NewObject<UBossEnemySkillAttackState>(this);
	if (BossSkillAttackState)
	{
		BossSkillAttackState->Initialize(this);
	}

	ChaseState = NewObject<UEnemyChaseState>(this);
	if (ChaseState)
	{
		ChaseState->Initialize(this);
	}

	DieState = NewObject<UEnemyDieState>(this);
	if (DieState)
	{
		DieState->Initialize(this);
	}

	InvestigateState = NewObject<UEnemyInvestigateState>(this);
	if (InvestigateState)
	{
		InvestigateState->Initialize(this);
	}

	ReturnState = NewObject<UEnemyReturnState>(this);
	if (ReturnState)
	{
		ReturnState->Initialize(this);
	}

	HitState = NewObject<UEnemyHitState>(this);
	if (HitState)
	{
		HitState->Initialize(this);
	}

	CurrentState = IdleState;
	if (CurrentState)
	{
		CurrentState->OnEnter();
	}
}

void UBossEnemyStateMachine::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
}

UEnemyStateBase* UBossEnemyStateMachine::GetCurrentState() const
{
	return Cast<UEnemyStateBase>(CurrentState);
}

UEnemyChaseState* UBossEnemyStateMachine::GetChaseState() const
{
	return ChaseState;
}

UBossEnemyAttackState* UBossEnemyStateMachine::GetBossAttackState() const
{
	return BossAttackState;
}

UBossEnemySkillAttackState* UBossEnemyStateMachine::GetBossSkillAttackState() const
{
	return BossSkillAttackState;
}

UEnemyDieState* UBossEnemyStateMachine::GetDieState() const
{
	return DieState;
}

UEnemyIdleState* UBossEnemyStateMachine::GetIdleState() const
{
	return IdleState;
}

UEnemyInvestigateState* UBossEnemyStateMachine::GetInvestigateState() const
{
	return InvestigateState;
}

UEnemyReturnState* UBossEnemyStateMachine::GetReturnState() const
{
	return ReturnState;
}

UEnemyHitState* UBossEnemyStateMachine::GetHitState() const
{
	return HitState;
}