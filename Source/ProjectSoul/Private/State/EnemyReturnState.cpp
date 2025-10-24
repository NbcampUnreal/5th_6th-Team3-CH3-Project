#include "State/EnemyReturnState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyReturnState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Return state."));
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
}
void UEnemyReturnState::OnExit()
{
    Super::OnExit();
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController) return;

    EnemyAIController->StopMovement();
    EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
}