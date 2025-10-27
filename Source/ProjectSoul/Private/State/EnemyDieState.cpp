#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Die state."));
    APSEnemy* Enemy = GetEnemyCharacter();//inefficiency
    if (!Enemy) return;
    Enemy->SetIsDead(true);
}

void UEnemyDieState::OnExit()
{
    Super::OnExit();
}

