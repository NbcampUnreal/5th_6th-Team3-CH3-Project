#include "State/PlayerHealState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerHealState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Heal State"));

	bCanDodge = false;

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);

		Character->PlayAnimMontage(Character->GetHealMontage());
	}
}

void UPlayerHealState::OnUpdate(float DeltaTime)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->OnUpdate(DeltaTime);
	}
}

void UPlayerHealState::OnExit()
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

	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Heal State"));
}

void UPlayerHealState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerHealState::CanDodge()
{
	bCanDodge = true;
}

void UPlayerHealState::Dodge()
{
	if (bCanDodge)
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			PSM->ChangeState(PSM->GetDodgeState());
		}
	}
}

void UPlayerHealState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerHealState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerHealState::HealEnd()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}