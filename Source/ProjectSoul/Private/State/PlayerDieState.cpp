#include "State/PlayerDieState.h"

void UPlayerDieState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Die State"));
}

void UPlayerDieState::OnUpdate(float DeltaTime)
{
}

void UPlayerDieState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Die State"));
}
