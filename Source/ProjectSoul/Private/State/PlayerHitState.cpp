#include "State/PlayerHitState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerHitState::OnEnter()
{
	bCanDodge = false;

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);

		Character->PlayAnimMontage(Character->GetHitMontage());
	}
}

void UPlayerHitState::OnUpdate(float DeltaTime)
{
}

void UPlayerHitState::OnExit()
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
}

void UPlayerHitState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerHitState::CanDodge()
{
	bCanDodge = true;
}

void UPlayerHitState::Dodge()
{
	if (bCanDodge)
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			PSM->ChangeState(PSM->GetDodgeState());
		}
	}
}

void UPlayerHitState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerHitState::HitEnd()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}