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

UEnemyStateMachine* UEnemyStateBase::GetEnemyStateMachine() const
{
	return Cast<UEnemyStateMachine>(StateMachine);
}

APSEnemy* UEnemyStateBase::GetEnemyCharacter() const
{
	if (UEnemyStateMachine* EnemyStateMachine = GetEnemyStateMachine())
	{
		return EnemyStateMachine->GetOwnerEnemy();
	}

	return nullptr;
}