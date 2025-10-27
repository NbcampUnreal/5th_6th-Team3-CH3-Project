#include "State/EnemyHitState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"

void UEnemyHitState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Hit state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy)->GetHitMontage();
    Anim->Montage_Play(Montage);
    EndDelegate.BindUObject(this, &UEnemyHitState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UEnemyHitState::OnExit()
{
    Super::OnExit();
}

void UEnemyHitState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Hit Montage Ended"));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    AAIController* EnemyAIController = Cast<AAIController>(Enemy->GetController());
    UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

    if (EnemyAIController == nullptr || BlackboardComp == nullptr)
    {
        return;
    }
    BlackboardComp->SetValueAsBool(TEXT("bIsHit"), false);
}