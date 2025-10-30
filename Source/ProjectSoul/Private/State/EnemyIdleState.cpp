#include "State/EnemyIdleState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyIdleState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Idle state."));
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController) return;

    UBlackboardComponent* BlackboardComp = EnemyAIController->GetBlackboardComponent();
    if (!BlackboardComp) return;

    FRotator SpawnRot = BlackboardComp->GetValueAsRotator(TEXT("SpawnRotation"));

    Enemy->SetActorRotation(SpawnRot);
}

void UEnemyIdleState::OnExit()
{
    Super::OnExit();
}