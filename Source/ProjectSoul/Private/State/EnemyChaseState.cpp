#include "State/EnemyChaseState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyChaseState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Chase state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy)
    {
        return;
    }
    Cast<APSEnemy>(Enemy)->SetMovementSpeed(Cast<APSEnemy>(Enemy)->GetChaseSpeed());
    AAIController* EnemyAIController= Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }


    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    if (!Target) return;

    EnemyAIController->SetFocus(Target);

    EnemyAIController->MoveToActor(
        Target,         
        100.0f,        
        true,         
        true,      
        true,         
        0,            
        true            
    );
}

void UEnemyChaseState::OnExit()
{
    Super::OnExit();
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    if (!EnemyAIController) return;

    EnemyAIController->StopMovement();
    EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
}