#include "AI/BTTask_SetState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "StateMachine/EnemyStateMachine.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyAttackState.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyDieState.h"
#include "State/EnemyInvestigateState.h"
#include "State/EnemyReturnState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetState::UBTTask_SetState()
{
    NodeName = TEXT("Set FSM State");
}

EBTNodeResult::Type UBTTask_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon)
		return EBTNodeResult::Failed;

	APSEnemy* EnemyChar = Cast<APSEnemy>(AICon->GetPawn());
	if (!EnemyChar)
		return EBTNodeResult::Failed;

	TObjectPtr<UEnemyStateMachine> StateMachine = EnemyChar->GetStateMachine();
	if (!StateMachine)
		return EBTNodeResult::Failed;

	switch (TargetState)
	{
	case EEnemyStateType::Idle:
		StateMachine->ChangeState(StateMachine->GetIdleState());
		break;

	case EEnemyStateType::Chase:
		StateMachine->ChangeState(StateMachine->GetChaseState());
		break;

	case EEnemyStateType::Attack:
		StateMachine->ChangeState(StateMachine->GetAttackState());
		break;

	case EEnemyStateType::Investigate:
		StateMachine->ChangeState(StateMachine->GetInvestigateState());
		break;

	case EEnemyStateType::Return:
		StateMachine->ChangeState(StateMachine->GetReturnState());
		break;

	case EEnemyStateType::Die:
		StateMachine->ChangeState(StateMachine->GetDieState());
		break;

	default:
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}