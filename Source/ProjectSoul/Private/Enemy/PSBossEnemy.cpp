#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "StateMachine/BossEnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


APSBossEnemy::APSBossEnemy()
{
	AIControllerClass = APSEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APSBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APSBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStateMachineBase* APSBossEnemy::CreateStateMachine()
{
	return NewObject<UBossEnemyStateMachine>(this);
}

UAnimMontage* APSBossEnemy::GetAttack1Montage() const
{
	return Attack_1_Montage;
}

UAnimMontage* APSBossEnemy::GetAttack2Montage() const
{
	return Attack_2_Montage;
}

UAnimMontage* APSBossEnemy::GetSkill1Montage() const
{
	return Skill_1_Montage;
}

UAnimMontage* APSBossEnemy::GetSkill2Montage() const
{
	return Skill_2_Montage;
}


void APSBossEnemy::Skill1Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy : Skill1"));
}


void APSBossEnemy::Skill2Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy : Skill2"));
}