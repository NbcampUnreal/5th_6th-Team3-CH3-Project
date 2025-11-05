#include "AI/BTTask_BossSetState.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "StateMachine/BossEnemyStateMachine.h"
#include "State/EnemyIdleState.h"
#include "State/BossEnemyAttackState.h"
#include "State/BossEnemySkillAttackState.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyDieState.h"
#include "State/EnemyInvestigateState.h"
#include "State/EnemyReturnState.h"
#include "State/BossEnemyHitState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossSetState::UBTTask_BossSetState()
{
	NodeName = TEXT("Set Boss Enemy FSM State");
}

EBTNodeResult::Type UBTTask_BossSetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon)
		return EBTNodeResult::Failed;

	APSBossEnemy* EnemyChar = Cast<APSBossEnemy>(AICon->GetPawn());
	if (!EnemyChar)
		return EBTNodeResult::Failed;

	UBossEnemyStateMachine* StateMachine = Cast<UBossEnemyStateMachine>(EnemyChar->GetStateMachine());
	if (!StateMachine)
		return EBTNodeResult::Failed;

	switch (TargetState)
	{
	case EBossEnemyStateType::Idle:
		StateMachine->ChangeState(StateMachine->GetIdleState());
		break;

	case EBossEnemyStateType::Chase:
		StateMachine->ChangeState(StateMachine->GetChaseState());
		break;

	case EBossEnemyStateType::Attack:
		StateMachine->ChangeState(StateMachine->GetBossAttackState());
		break;

	case EBossEnemyStateType::Skill:
		StateMachine->ChangeState(StateMachine->GetBossSkillAttackState());
		break;

	case EBossEnemyStateType::Investigate:
		StateMachine->ChangeState(StateMachine->GetInvestigateState());
		break;

	case EBossEnemyStateType::Return:
		StateMachine->ChangeState(StateMachine->GetReturnState());
		break;

	case EBossEnemyStateType::Die:
		StateMachine->ChangeState(StateMachine->GetDieState());
		break;

	case EBossEnemyStateType::Hit:
		StateMachine->ChangeState(StateMachine->GetHitState());
		break;

	default:
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
