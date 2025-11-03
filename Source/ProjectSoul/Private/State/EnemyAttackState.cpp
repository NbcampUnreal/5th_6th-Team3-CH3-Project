#include "State/EnemyAttackState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

void UEnemyAttackState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Attack state."));
    ACharacter* Enemy = GetEnemyCharacter();
    if (!Enemy) return;
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
    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy) ->GetAttackMontage();
    Anim->Montage_Play(Montage);
    EndDelegate.BindUObject(this, &UEnemyAttackState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UEnemyAttackState::OnExit()
{
    Super::OnExit();
}

void UEnemyAttackState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    
    ACharacter* Enemy = GetEnemyCharacter();
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