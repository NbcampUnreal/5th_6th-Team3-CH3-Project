#include "State/EnemyChaseState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyChaseState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : ChaseState"));

    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        return;
    }
    APSEnemy* BaseEnemy = Cast<APSEnemy>(Enemy);
    if (!BaseEnemy)
    {
        return;
    }
    BaseEnemy->SetMovementSpeed(BaseEnemy->GetChaseSpeed());
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController)
    {
        return;
    }

    UBlackboardComponent* BlackboardComp = EnemyAIController->GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }
    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    if (!Target)
    {
        return;
    }
    EPathFollowingRequestResult::Type Result = EnemyAIController->MoveToActor(Target, 100.0f);
}

void UEnemyChaseState::OnExit()
{
    Super::OnExit();
    APSEnemy* Enemy = Cast<APSEnemy>(GetEnemyCharacter());
    if (!Enemy) return;

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController) return;

    EnemyAIController->StopMovement();
    EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
}