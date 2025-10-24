#include "State/EnemyDieState.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Die state."));
}
void UEnemyDieState::OnExit()
{
    Super::OnExit();
}