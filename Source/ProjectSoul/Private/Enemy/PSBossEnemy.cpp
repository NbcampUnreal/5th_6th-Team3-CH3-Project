#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "StateMachine/BossEnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "Components/WidgetComponent.h"
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

void APSBossEnemy::ShowHealthWidget(bool bShow)
{

}

void APSBossEnemy::ShowHitHealthWidget()
{

}

void APSBossEnemy::HiddenHitHealthWidget()
{

}