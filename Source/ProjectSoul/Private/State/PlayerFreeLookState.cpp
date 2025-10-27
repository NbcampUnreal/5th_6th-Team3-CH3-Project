#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerDieState.h"
#include "Character/PSCharacter.h"
#include "StateMachine/PlayerStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerFreeLookState::OnEnter()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetTargetingCamera();
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetNormalWalkSpeed();
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		Character->bUseControllerRotationYaw = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Free Look State"));
}

void UPlayerFreeLookState::OnUpdate(float DeltaTime)
{
}

void UPlayerFreeLookState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Free Look State"));
}

void UPlayerFreeLookState::Move(const FVector2D& Value)
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		FRotator ControlRotation = Character->GetControlRotation();
		FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Character->AddMovementInput(Forward, Value.X);
		Character->AddMovementInput(Right, Value.Y);
	}
}

void UPlayerFreeLookState::Look(const FVector2D& Value)
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->AddControllerPitchInput(Value.Y);
		Character->AddControllerYawInput(Value.X);
	}
}

void UPlayerFreeLookState::StartSprint()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(true);
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetSprintWalkSpeed();
	}
}

void UPlayerFreeLookState::StopSprint()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsSprinting(false);
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetNormalWalkSpeed();
	}
}

void UPlayerFreeLookState::StartJump()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->Jump();
	}
}

void UPlayerFreeLookState::StopJump()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->StopJumping();
	}
}

void UPlayerFreeLookState::Attack()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetAttackState());
	}
}

void UPlayerFreeLookState::Lock()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			Character->SetIsTargeting(true);
			PSM->ChangeState(PSM->GetTargetingState());
		}
	}
}

void UPlayerFreeLookState::Dodge()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			PSM->SetPrevState(this);
			PSM->ChangeState(PSM->GetDodgeState());
		}
	}
}

void UPlayerFreeLookState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerFreeLookState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}