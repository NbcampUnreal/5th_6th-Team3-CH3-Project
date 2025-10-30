#include "State/BossEnemyAttackState.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"

void UBossEnemyAttackState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : BossAttack state."));
    ACharacter* Enemy = GetEnemyCharacter();
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
    UAnimMontage* Montage1 = Cast<APSEnemy>(Enemy)->GetAttackMontage();
    UAnimMontage* Montage2 = Cast<APSBossEnemy>(Enemy)->GetAttackMontage();
    UAnimMontage* Montage3 = Cast<APSBossEnemy>(Enemy)->GetAttackMontage();
    Anim->Montage_Play(Montage1);
    EndDelegate.BindUObject(this, &UBossEnemyAttackState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage1);
}

void UBossEnemyAttackState::OnExit()
{
    Super::OnExit();
}

void UBossEnemyAttackState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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