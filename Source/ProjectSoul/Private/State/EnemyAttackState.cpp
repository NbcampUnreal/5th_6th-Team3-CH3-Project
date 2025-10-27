#include "State/EnemyAttackState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnemyAttackState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Attack state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }
    BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), true);
    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    EnemyAIController->SetFocus(Target);

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy) ->GetAttackMontage();
    Anim->Montage_Play(Montage);
    EndDelegate.BindUObject(this, &UEnemyAttackState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UEnemyAttackState::OnExit()
{
    Super::OnExit();
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
}

void UEnemyAttackState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Attack Montage Ended"));
    BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), false);
    BlackboardComp->SetValueAsBool(TEXT("bInAttackRange"), false);
}