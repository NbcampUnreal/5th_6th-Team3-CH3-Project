#include "State/PlayerDodgeState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerDodgeState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Dodge State"));

	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);
		Character->ConsumeStaminaForDodge();
		Character->PlayAnimMontage(Character->GetDodgeMontage());
	}
}

void UPlayerDodgeState::OnUpdate(float DeltaTime)
{
}

void UPlayerDodgeState::OnExit()
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

	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Dodge State"));
}

void UPlayerDodgeState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
	}
}

void UPlayerDodgeState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerDodgeState::DodgeEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Call Dodge End"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}