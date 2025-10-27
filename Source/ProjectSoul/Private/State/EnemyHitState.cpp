#include "State/EnemyHitState.h"
#include "Enemy/PSEnemy.h"

void UEnemyHitState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Hit state."));
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
    UE_LOG(LogTemp, Warning, TEXT("Hit Montage Ended"));
}