#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Die state."));
    ACharacter* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    Cast<APSEnemy>(Enemy)->PlayAnimMontage(Cast<APSEnemy>(Enemy)->GetDieMontage());
}
void UEnemyDieState::OnExit()
{
    Super::OnExit();
}