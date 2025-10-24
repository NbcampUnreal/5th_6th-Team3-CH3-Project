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
}

void UPlayerAttackState::OnUpdate(float DeltaTime)
{
}

void UPlayerAttackState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit Attack State"));
}

void UPlayerAttackState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerAttackState::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Call Attack End in AttackState"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}