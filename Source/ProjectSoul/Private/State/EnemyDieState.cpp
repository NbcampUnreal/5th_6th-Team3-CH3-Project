#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Die state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    UAnimMontage* Montage = Cast<APSEnemy>(Enemy)->GetDieMontage();
    Anim->Montage_Play(Montage);
    EndDelegate.BindUObject(this, &UEnemyDieState::OnMontageEnded);
    Anim->Montage_SetEndDelegate(EndDelegate, Montage);
}

void UEnemyDieState::OnExit()
{
    Super::OnExit();
}

void UEnemyDieState::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Die Montage Ended"));
    ACharacter* Enemy = GetEnemyCharacter();
    Cast<APSEnemy>(Enemy)->Destroy();
}