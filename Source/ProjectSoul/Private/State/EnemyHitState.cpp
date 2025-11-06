#include "State/EnemyHitState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"

void UEnemyHitState::OnEnter()
{
    Super::OnEnter();

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

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy)->GetHitMontage();
    Anim->Montage_Play(Montage);

    EndDelegate.BindUObject(this, &UEnemyHitState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UEnemyHitState::OnExit()
{
    Super::OnExit();

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

    Cast<APSEnemyAIController>(EnemyAIController)->SetSightAngle(180.0f);

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    Anim->StopAllMontages(0.1f);
}

void UEnemyHitState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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
}