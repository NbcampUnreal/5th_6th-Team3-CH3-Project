#include "State/PlayerAttackState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"
#include "Weapon/PSWeaponBase.h"

void UPlayerAttackState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Attack State"));

	bCanNextCombo = false;
	bDoNextCombo = false;
	bCanDodge = false;
	
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);
		Character->bUseControllerRotationYaw = false;

		Character->ConsumeStaminaForAttack();
		Character->PlayAnimMontage(Character->GetAttackMontage(CurrentComboIndex));
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
		Character->GetEquippedRightWeapon()->DisableWeaponCollision();

		if (UAnimInstance* AnimInst = Character->GetMesh()->GetAnimInstance())
		{
			if (AnimInst->IsAnyMontagePlaying())
			{
				if (!bDoNextCombo)
				{
					AnimInst->StopAllMontages(0.1f);
					CurrentComboIndex = 0;
				}
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

void UPlayerAttackState::CanDodge()
{
	bCanDodge = true;
}

void UPlayerAttackState::Dodge()
{
	if (bCanDodge)
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			PSM->ChangeState(PSM->GetDodgeState());
		}
	}
}

void UPlayerAttackState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerAttackState::Attack()
{
	if (bCanNextCombo)
	{
		bCanNextCombo = false;
		bDoNextCombo = true;
	}
}

void UPlayerAttackState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerAttackState::NextComboWindow()
{
	bCanNextCombo = true;
}

void UPlayerAttackState::StartNextCombo()
{
	if (bDoNextCombo)
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			UE_LOG(LogTemp, Warning, TEXT("Player: Start Next Combo"));
			CurrentComboIndex++;
			PSM->ChangeState(this);
		}
	}
}

void UPlayerAttackState::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Call Attack End"));
	
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		CurrentComboIndex = 0;
		PSM->ChangeState(PSM->GetPrevState());
	}
}