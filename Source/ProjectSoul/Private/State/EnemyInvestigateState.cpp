#include "State/EnemyInvestigateState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AITypes.h"     
void UEnemyInvestigateState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Investigate state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }


    FVector TargetLastKnownLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLastKnownLocation"));
    if (TargetLastKnownLocation.IsNearlyZero())
    {
        return;
    }
    EnemyAIController->SetFocalPoint(TargetLastKnownLocation);

    EnemyAIController->MoveToLocation(
        TargetLastKnownLocation,
        100.0f,
        true,
        true,
        true,
        false
    );
    if (UPathFollowingComponent* PFC = EnemyAIController->GetPathFollowingComponent())
    {
        PFC->OnRequestFinished.AddUObject(this, &UEnemyInvestigateState::HandleMoveFinished);
    }
}

void UEnemyInvestigateState::OnExit()
{
    Super::OnExit();
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController) return;

    if (UPathFollowingComponent* PFC = EnemyAIController->GetPathFollowingComponent())
    {
        PFC->OnRequestFinished.RemoveAll(this);
    }

    EnemyAIController->StopMovement();
    EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
}

void UEnemyInvestigateState::HandleMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.IsSuccess())
    {
        UE_LOG(LogTemp, Warning, TEXT("success Investigate"));
        ACharacter* Enemy = GetEnemyCharacter();
        if (!Enemy) return;

        AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
        if (!EnemyAIController) return;

        UBlackboardComponent* BlackboardComp = EnemyAIController->GetBlackboardComponent();
        if (!BlackboardComp) return;

        BlackboardComp->SetValueAsBool(TEXT("bIsInvestigating"), false);
        BlackboardComp->SetValueAsBool(TEXT("bIsReturning"), true);
    }
}