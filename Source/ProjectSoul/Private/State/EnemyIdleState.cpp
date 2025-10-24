#include "State/EnemyIdleState.h"

void UEnemyIdleState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Idle state."));
}
void UEnemyIdleState::OnExit()
{
    Super::OnExit();
}