#include "State/PlayerTargetingState.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerThrowState.h"
#include "State/PlayerHealState.h"
#include "State/PlayerDieState.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/PSPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/PSEnemy.h"

void UPlayerTargetingState::OnEnter()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->SetIsTargeting(true);
		Character->SetTargetingCamera();

		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetTargetingWalkSpeed();
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->bUseControllerRotationYaw = true;

		Character->GetCurrentTarget()->ShowHealthWidget(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player: Enter Targeting State"));
}

void UPlayerTargetingState::OnUpdate(float DeltaTime)
{
	if (!IsTargetValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: Target is not valid"));
		Unlock();
		return;
	}

	if (IsTargetTooFar())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: Target is too far"));
		Unlock();
		return;
	}

	CalculateTargetRotation(DeltaTime);
}

void UPlayerTargetingState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Exit Targeting State"));
}

void UPlayerTargetingState::Move(const FVector2D& Value)
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

void UPlayerTargetingState::Look(const FVector2D& Value)
{
}

void UPlayerTargetingState::StartSprint()
{
}

void UPlayerTargetingState::StopSprint()
{
}

void UPlayerTargetingState::StartJump()
{
}

void UPlayerTargetingState::StopJump()
{
}

void UPlayerTargetingState::Attack()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetAttackState());
	}
}

void UPlayerTargetingState::Unlock()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			Character->SetIsTargeting(false);

			Character->GetCurrentTarget()->ShowHealthWidget(false);
			Character->SetCurrentTarget(nullptr);

			PSM->ChangeState(PSM->GetFreeLookState());
		}
	}
}

void UPlayerTargetingState::Dodge()
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

void UPlayerTargetingState::Hit()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetHitState());
	}
}

void UPlayerTargetingState::Throw()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetThrowState());
	}
}

void UPlayerTargetingState::Heal()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->SetPrevState(this);
		PSM->ChangeState(PSM->GetHealState());
	}
}

void UPlayerTargetingState::Die()
{
	if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
	{
		PSM->ChangeState(PSM->GetDieState());
	}
}

void UPlayerTargetingState::CalculateTargetRotation(float DeltaTime)
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		AActor* CurrentTarget = Character->GetCurrentTarget();
		if (!CurrentTarget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player: No Target."));
			Unlock();
			return;
		}

		if (APSPlayerController* PC = Cast<APSPlayerController>(Character->GetController()))
		{
			FVector PlayerLocation = Character->GetActorLocation();
			FVector TargetLocation = CurrentTarget->GetActorLocation();

			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
			LookAtRotation.Pitch = -30.0f;
			FRotator ControlRotation = PC->GetControlRotation();

			FRotator NewRotation = FMath::RInterpTo(ControlRotation, LookAtRotation, DeltaTime, 7.0f);
			PC->SetControlRotation(NewRotation);
		}
	}
}

float UPlayerTargetingState::CalculateTargetDistance()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		AActor* CurrentTarget = Character->GetCurrentTarget();
		if (CurrentTarget)
		{
			return FVector::Distance(CurrentTarget->GetActorLocation(), Character->GetActorLocation());
		}
	}

	return TNumericLimits<float>::Max();
}

bool UPlayerTargetingState::IsTargetTooFar()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		return CalculateTargetDistance() > Character->GetMaxTargetDistance();
	}

	return false;
}

bool UPlayerTargetingState::IsTargetValid()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		return IsValid(Character->GetCurrentTarget());
	}

	return false;
}