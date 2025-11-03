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
		Character->bUseControllerRotationYaw = false;

		FVector DodgeDir = CalculateDodgeDirection();
		FRotator DodgeRotation = DodgeDir.Rotation();
		Character->SetActorRotation(DodgeRotation);

		Character->SetIsSprinting(false);
		Character->ConsumeStaminaForDodge();
		Character->PlayAnimMontage(Character->GetDodgeMontage());
	}
}

void UPlayerDodgeState::OnUpdate(float DeltaTime)
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->GetPrevState()->OnUpdate(DeltaTime);
	}
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

void UPlayerDodgeState::InvulnerableStart()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsInvulnerable(true);
	}
}

void UPlayerDodgeState::InvulnerableEnd()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsInvulnerable(false);
	}
}

FVector UPlayerDodgeState::CalculateDodgeDirection()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		FVector2D Input = Character->GetLastMoveInput();

		FRotator ControlRotation = Character->GetControlRotation();
		FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		FVector DodgeDir;

		if (!Input.IsNearlyZero())
		{
			DodgeDir = (Forward * Input.X + Right * Input.Y).GetSafeNormal();
		}
		else
		{
			DodgeDir = Character->GetActorForwardVector();
		}

		return DodgeDir;
	}

	return FVector::ZeroVector;
}