#include "State/EnemyReturnState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyReturnState::OnEnter()
{
    Super::OnEnter();

    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        return;
    }

    Cast<APSEnemy>(Enemy)->SetMovementSpeed(Cast<APSEnemy>(Enemy)->GetWalkSpeed());

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }

    FVector SpawnPointLocation = BlackboardComp->GetValueAsVector(TEXT("SpawnPointLocation"));
    if (SpawnPointLocation.IsNearlyZero())
    {
        return;
    }

    EnemyAIController->MoveToLocation(
        SpawnPointLocation,
        100.0f,        
        true,          
        true,         
        true,          
        false         
    );

    if (UPathFollowingComponent* PFC = EnemyAIController->GetPathFollowingComponent())
    {
        PFC->OnRequestFinished.AddUObject(this, &UEnemyReturnState::HandleMoveFinished);
    }
}

void UEnemyReturnState::OnExit()
{
    Super::OnExit();

    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        return;
    }

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController)
    {
        return;
    }

    EnemyAIController->StopMovement();

    if (UPathFollowingComponent* PFC = EnemyAIController->GetPathFollowingComponent())
    {
        PFC->OnRequestFinished.RemoveAll(this);
    }
}

void UEnemyReturnState::HandleMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.IsSuccess())
    {
        ACharacter* Enemy = GetEnemyCharacter();
        if (!Enemy)
        {
            return;
        }

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

        BlackboardComp->SetValueAsBool(TEXT("bIsReturning"), false);
    }
}