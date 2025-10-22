#include "State/PlayerTargetingState.h"
#include "Character/PSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/PSPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "StateMachine/PlayerStateMachine.h"
#include "State/PlayerFreeLookState.h"

void UPlayerTargetingState::OnEnter()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetTargetingWalkSpeed();
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->bUseControllerRotationYaw = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Enter Targeting State"));
}

void UPlayerTargetingState::OnUpdate(float DeltaTime)
{
	if (IsTargetTooFar())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is too far."));

		if (APSCharacter* Character = GetPlayerCharacter())
		{
			Character->SetCurrentTarget(nullptr);
			Unlock();
			return;
		}
	}

	CalculateTargetRotation(DeltaTime);
}

void UPlayerTargetingState::OnExit()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		Character->bUseControllerRotationYaw = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Exit Targeting State"));
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
}

void UPlayerTargetingState::Unlock()
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		if (UPlayerStateMachine* PSM = GetPlayerStateMachine())
		{
			Character->SetIsTargeting(false);
			PSM->ChangeState(PSM->GetFreeLookState());
		}
	}
}

void UPlayerTargetingState::CalculateTargetRotation(float DeltaTime)
{
	if (APSCharacter* Character = GetPlayerCharacter())
	{
		AActor* CurrentTarget = Character->GetCurrentTarget();
		if (!CurrentTarget)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Target."));
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

			FRotator NewRotation = FMath::RInterpTo(ControlRotation, LookAtRotation, DeltaTime, 10.0f);
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
