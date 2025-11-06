#include "State/BossEnemyAttackState.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"

void UBossEnemyAttackState::OnEnter()
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

    Cast<APSEnemyAIController>(EnemyAIController)->SetSightAngle(180.0f);

    BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), true);

    AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    if (Target)
    {
        FVector ToTarget = (Target->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal2D();
        FRotator LookRot = FRotationMatrix::MakeFromX(ToTarget).Rotator();
        LookRot.Pitch = 0.f;
        LookRot.Roll = 0.f;

        Enemy->SetActorRotation(LookRot);
        EnemyAIController->SetControlRotation(LookRot);
    }

    int32 RandIndex = FMath::RandRange(0, 2);
    UAnimMontage* Montage1 = Cast<APSEnemy>(Enemy)->GetAttackMontage();
    UAnimMontage* Montage2 = Cast<APSBossEnemy>(Enemy)->GetAttack1Montage();
    UAnimMontage* Montage3 = Cast<APSBossEnemy>(Enemy)->GetAttack2Montage();
    UAnimMontage* MontageToPlay = nullptr;
    if (RandIndex == 0 && Montage1)
    {
        MontageToPlay = Montage1;
    }
    else if (RandIndex == 1 && Montage2)
    {
        MontageToPlay = Montage2;
    }
    else if (RandIndex == 2 && Montage3)
    {
        MontageToPlay = Montage3;
    }

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    Anim->Montage_Play(MontageToPlay);
    EndDelegate.BindUObject(this, &UBossEnemyAttackState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, MontageToPlay);
}

void UBossEnemyAttackState::OnExit()
{
    Super::OnExit();

    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy)
    {
        return;
    }

    Cast<APSEnemy>(Enemy)->DisableWeaponCollisionNotify();
}

void UBossEnemyAttackState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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

    BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), false);
    BlackboardComp->SetValueAsBool(TEXT("bInAttackRange"), false);
}