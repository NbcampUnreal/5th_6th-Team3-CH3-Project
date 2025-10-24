#include "StateMachine/EnemyStateMachine.h"

#include "Enemy/PSEnemy.h"
#include "State/EnemyAttackState.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyDieState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyInvestigateState.h"
#include "State/EnemyReturnState.h"

void UEnemyStateMachine::Initialize(ACharacter* InOwner)
{
	Super::Initialize(InOwner);

	IdleState = NewObject<UEnemyIdleState>(this);
	if (IdleState)
	{
		IdleState->Initialize(this);
	}

	AttackState = NewObject<UEnemyAttackState>(this);
	if (AttackState)
	{
		AttackState->Initialize(this);
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

	CurrentState = IdleState;
	if (CurrentState)
	{
		CurrentState->OnEnter();
	}
}

void UEnemyStateMachine::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
}

UEnemyStateBase* UEnemyStateMachine::GetCurrentState() const
{
	return Cast<UEnemyStateBase>(CurrentState);
}


APSEnemy* UEnemyStateMachine::GetOwnerEnemy() const
{
	return Cast<APSEnemy>(OwnerCharacter);
}

UEnemyChaseState* UEnemyStateMachine::GetChaseState() const 
{
	return ChaseState;
}

UEnemyAttackState* UEnemyStateMachine::GetAttackState() const
{
	return AttackState;
}

UEnemyDieState* UEnemyStateMachine::GetDieState() const
{
	return DieState;
}

UEnemyIdleState* UEnemyStateMachine::GetIdleState() const
{
	return IdleState;
}

UEnemyInvestigateState* UEnemyStateMachine::GetInvestigateStateState() const
{
	return InvestigateState;
}

UEnemyReturnState* UEnemyStateMachine::GetReturnState() const
{
	return ReturnState;
}
