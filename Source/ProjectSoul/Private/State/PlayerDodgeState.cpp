#include "State/PlayerDodgeState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerDodgeState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter Dodge State"));

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->PlayAnimMontage(Character->GetDodgeMontage());
	}
}

void UPlayerDodgeState::OnUpdate(float DeltaTime)
{
}

void UPlayerDodgeState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit Dodge State"));
}

void UPlayerDodgeState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerDodgeState::DodgeEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Call Dodge End in AttackState"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}