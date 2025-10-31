#include "State/PlayerAttackState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerAttackState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Attack State"));

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);
		Character->bUseControllerRotationYaw = false;

		Character->ConsumeStaminaForAttack();
		Character->PlayAnimMontage(Character->GetAttackMontage());
	}
}

void UPlayerAttackState::OnUpdate(float DeltaTime)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->OnUpdate(DeltaTime);
	}
}

void UPlayerAttackState::OnExit()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		if (UAnimInstance* AnimInst = Character->GetMesh()->GetAnimInstance())
		{
			if (AnimInst->IsAnyMontagePlaying())
			{
				AnimInst->StopAllMontages(0.1f);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Attack State"));
}

void UPlayerAttackState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerAttackState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerAttackState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerAttackState::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Call Attack End"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}