#include "State/EnemyStateBase.h"
#include "StateMachine/EnemyStateMachine.h"
#include "Enemy/PSEnemy.h"
void UEnemyStateBase::OnEnter()
{
}

void UEnemyStateBase::OnUpdate(float DeltaTime)
{
}

void UEnemyStateBase::OnExit()
{
}

UStateMachineBase* UEnemyStateBase::GetEnemyStateMachine() const
{
	return StateMachine;
}

ACharacter* UEnemyStateBase::GetEnemyCharacter() const
{
	if (UStateMachineBase* EnemyStateMachine = GetEnemyStateMachine())
	{
		return EnemyStateMachine->GetOwnerCharacter();
	}

	return nullptr;
}