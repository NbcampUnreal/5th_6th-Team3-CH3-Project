#include "State/PlayerStateBase.h"
#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"

void UPlayerStateBase::OnEnter()
{
}

void UPlayerStateBase::OnUpdate(float DeltaTime)
{
}

void UPlayerStateBase::OnExit()
{
}

void UPlayerStateBase::Move(const FVector2D& Value)
{
}

void UPlayerStateBase::Look(const FVector2D& Value)
{
}

void UPlayerStateBase::StartSprint()
{
}

void UPlayerStateBase::StopSprint()
{
}

void UPlayerStateBase::StartJump()
{
}

void UPlayerStateBase::StopJump()
{
}

void UPlayerStateBase::Attack()
{
}

void UPlayerStateBase::Lock()
{
}

void UPlayerStateBase::Unlock()
{
}

void UPlayerStateBase::CanDodge()
{
}

void UPlayerStateBase::Dodge()
{
}

void UPlayerStateBase::Hit()
{
}

void UPlayerStateBase::Throw()
{
}

void UPlayerStateBase::Die()
{
}

UPlayerStateMachine* UPlayerStateBase::GetPlayerStateMachine() const
{
	return Cast<UPlayerStateMachine>(StateMachine);
}

APSCharacter* UPlayerStateBase::GetPlayerCharacter() const
{
	if (UPlayerStateMachine* PlayerStateMachine = GetPlayerStateMachine())
	{
		return PlayerStateMachine->GetOwnerCharacter();
	}

	return nullptr;
}