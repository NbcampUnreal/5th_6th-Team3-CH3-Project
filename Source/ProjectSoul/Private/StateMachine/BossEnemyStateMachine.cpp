#include "StateMachine/BossEnemyStateMachine.h"
#include "State/BossEnemySkillAttackState.h"
void UBossEnemyStateMachine::Initialize(ACharacter* InOwner)
{
	Super::Initialize(InOwner);
	BossEnemySkillAttackState = NewObject<UBossEnemySkillAttackState>(this);
	if (BossEnemySkillAttackState)
	{
		BossEnemySkillAttackState->Initialize(this);
	}
}

UBossEnemySkillAttackState* UBossEnemyStateMachine::GetBossEnemySkillAttackState() const
{
	return BossEnemySkillAttackState;
}
