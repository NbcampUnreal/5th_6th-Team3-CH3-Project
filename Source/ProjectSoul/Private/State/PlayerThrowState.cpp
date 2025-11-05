#include "State/PlayerThrowState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerThrowState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Throw State"));

	bCanDodge = false;

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);

		Character->PlayAnimMontage(Character->GetThrowMontage());
	}
}

void UPlayerThrowState::OnUpdate(float DeltaTime)
{
}

void UPlayerThrowState::OnExit()
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

	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Throw State"));
}

void UPlayerThrowState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerThrowState::CanDodge()
{
	bCanDodge = true;
}

void UPlayerThrowState::Dodge()
{
	if (bCanDodge)
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			PSM->ChangeState(PSM->GetDodgeState());
		}
	}
}

void UPlayerThrowState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerThrowState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerThrowState::ThrowEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Call Throw End"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}