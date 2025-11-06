#include "State/BossEnemyHitState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"

void UBossEnemyHitState::OnEnter()
{
    Super::OnEnter();

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

    Cast<APSEnemyAIController>(EnemyAIController)->SetSightAngle(180.0f);

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy)->GetHitMontage();
    Anim->StopAllMontages(0.1f);
    Anim->Montage_Play(Montage);
    EndDelegate.BindUObject(this, &UBossEnemyHitState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UBossEnemyHitState::OnExit()
{
    Super::OnExit();
}

void UBossEnemyHitState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        return;
    }

    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }

    BlackboardComp->SetValueAsBool(TEXT("bIsHit"), false);
}