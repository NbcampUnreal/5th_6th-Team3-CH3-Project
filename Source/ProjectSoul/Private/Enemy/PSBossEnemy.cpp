#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "Components/WidgetComponent.h"
APSBossEnemy::APSBossEnemy()
	:APSEnemy()
{
	
}

void APSBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APSBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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