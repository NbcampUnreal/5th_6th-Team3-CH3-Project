#include "State/BossEnemySkillAttackState.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"

void UBossEnemySkillAttackState::OnEnter()
{
	Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Boss Skill state."));
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }
    Cast<APSEnemyAIController>(EnemyAIController)->SetSightAngle(180.0f);
    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
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
    int32 RandIndex = FMath::RandRange(0, 1);
    UAnimMontage* Montage1 = Cast<APSBossEnemy>(Enemy)->GetSkill1Montage();
    UAnimMontage* Montage2 = Cast<APSBossEnemy>(Enemy)->GetSkill2Montage();
    UAnimMontage* MontageToPlay = nullptr;
    if (RandIndex == 0 && Montage1)
    {
        MontageToPlay = Montage1;
    }
    else if (RandIndex == 1 && Montage2)
    {
        MontageToPlay = Montage2;
    }
    Anim->Montage_Play(MontageToPlay);
    EndDelegate.BindUObject(this, &UBossEnemySkillAttackState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, MontageToPlay);
}

void UBossEnemySkillAttackState::OnExit()
{
	Super::OnExit();
}

void UBossEnemySkillAttackState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }
    BlackboardComp->SetValueAsBool(TEXT("bCollSkill"), true);
    BlackboardComp->SetValueAsBool(TEXT("bInAttackRange"), false);
    Enemy->GetWorldTimerManager().SetTimer(
        CoolTimerHandle,
        FTimerDelegate::CreateLambda([BlackboardComp]()
            {
                BlackboardComp->SetValueAsBool(TEXT("bCollSkill"), false);
                UE_LOG(LogTemp, Warning, TEXT("Boss Skill cooldown finished."));
            }),
        5.f,
        false
    );

}
