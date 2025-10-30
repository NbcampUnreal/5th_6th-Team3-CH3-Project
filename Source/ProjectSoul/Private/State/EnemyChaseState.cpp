#include "State/EnemyChaseState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyChaseState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("==== EnemyChaseState::OnEnter ===="));

    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Enemy: %s"), *Enemy->GetName());

    APSEnemy* BaseEnemy = Cast<APSEnemy>(Enemy);
    if (!BaseEnemy)
    {
        UE_LOG(LogTemp, Error, TEXT("Cast<APSEnemy> failed"));
        return;
    }

    BaseEnemy->SetMovementSpeed(BaseEnemy->GetChaseSpeed());

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyAIController is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *EnemyAIController->GetName());

    UBlackboardComponent* BlackboardComp = EnemyAIController->GetBlackboardComponent();
    if (!BlackboardComp)
    {
        UE_LOG(LogTemp, Error, TEXT("BlackboardComp is NULL"));
        return;
    }

    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    if (!Target)
    {
        UE_LOG(LogTemp, Error, TEXT("TargetActor is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *Target->GetName());

    EPathFollowingRequestResult::Type Result = EnemyAIController->MoveToActor(Target, 100.0f);
    UE_LOG(LogTemp, Warning, TEXT("MoveToActor Result = %d"), (int32)Result);
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