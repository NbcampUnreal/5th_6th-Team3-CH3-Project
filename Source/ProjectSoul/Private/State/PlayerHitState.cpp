#include "State/PlayerHitState.h"

void UPlayerHitState::OnEnter()
{
	UE_LOG(LogTemp, Log, TEXT("Player: Enter Player Hit State"));
}

void UPlayerHitState::OnUpdate(float DeltaTime)
{
}

void UPlayerHitState::OnExit()
{
	UE_LOG(LogTemp, Log, TEXT("Player: Exit Player Hit State"));
}