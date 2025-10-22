#include "State/PlayerAttackState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerAttackState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter Attack State"));

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->PlayAnimMontage(Character->GetAttackMontage());
	}

	GetWorld()->GetTimerManager().SetTimer(
		TestTimer,
		this,
		&UPlayerAttackState::AttackEnd,
		1.0f,
		false
	);
}

void UPlayerAttackState::OnUpdate(float DeltaTime)
{
}

void UPlayerAttackState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit Attack State"));
}

void UPlayerAttackState::AttackEnd()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}