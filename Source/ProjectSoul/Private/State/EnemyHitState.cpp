#include "State/EnemyHitState.h"
#include "Enemy/PSEnemy.h"

void UEnemyHitState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Hit state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    Cast<APSEnemy>(Enemy)->PlayAnimMontage(Cast<APSEnemy>(Enemy)->GetHitMontage());
}
void UEnemyHitState::OnExit()
{
    Super::OnExit();
}