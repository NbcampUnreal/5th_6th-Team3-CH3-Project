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

	GetWorld()->GetTimerManager().SetTimer(
		TestTimer,
		this,
		&UPlayerDodgeState::DodgeEnd,
		1.0f,
		false
	);
}

void UPlayerDodgeState::OnUpdate(float DeltaTime)
{
}

void UPlayerDodgeState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit Dodge State"));
}

void UPlayerDodgeState::DodgeEnd()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}