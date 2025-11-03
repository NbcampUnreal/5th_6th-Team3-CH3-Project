#include "State/PlayerHitState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerHitState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Hit State"));

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

	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Hit State"));
}

void UPlayerHitState::Look(const FVector2D& Value)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->Look(Value);
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
	UE_LOG(LogTemp, Warning, TEXT("Player: Call Hit End"));

	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetPrevState());
	}
}