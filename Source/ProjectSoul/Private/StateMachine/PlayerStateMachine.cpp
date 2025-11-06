#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerThrowState.h"
#include "State/PlayerHealState.h"
#include "State/PlayerDieState.h"

void UPlayerStateMachine::Initialize(ACharacter* InOwner)
{
	Super::Initialize(InOwner);

	FreeLookState = NewObject<UPlayerFreeLookState>(this);
	if (FreeLookState)
	{
		FreeLookState->Initialize(this);
	}

	TargetingState = NewObject<UPlayerTargetingState>(this);
	if (TargetingState)
	{
		TargetingState->Initialize(this);
	}

	AttackState = NewObject<UPlayerAttackState>(this);
	if (AttackState)
	{
		AttackState->Initialize(this);
	}

	DodgeState = NewObject<UPlayerDodgeState>(this);
	if (DodgeState)
	{
		DodgeState->Initialize(this);
	}

	HitState = NewObject<UPlayerHitState>(this);
	if (HitState)
	{
		HitState->Initialize(this);
	}

	ThrowState = NewObject<UPlayerThrowState>(this);
	if (ThrowState)
	{
		ThrowState->Initialize(this);
	}

	HealState = NewObject<UPlayerHealState>(this);
	if (HealState)
	{
		HealState->Initialize(this);
	}

	DieState = NewObject<UPlayerDieState>(this);
	if (DieState)
	{
		DieState->Initialize(this);
	}

	CurrentState = FreeLookState;
	if (CurrentState)
	{
		CurrentState->OnEnter();
	}
}

void UPlayerStateMachine::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
}

UPlayerStateBase* UPlayerStateMachine::GetCurrentState() const
{
	return Cast<UPlayerStateBase>(CurrentState);
}

UPlayerStateBase* UPlayerStateMachine::GetPrevState() const
{
	return PrevState;
}

void UPlayerStateMachine::SetPrevState(UPlayerStateBase* NewPrevState)
{
	PrevState = NewPrevState;
}

APSCharacter* UPlayerStateMachine::GetOwnerCharacter() const
{
	return Cast<APSCharacter>(OwnerCharacter);
}

UPlayerFreeLookState* UPlayerStateMachine::GetFreeLookState() const
{
	return FreeLookState;
}

UPlayerTargetingState* UPlayerStateMachine::GetTargetingState() const
{
	return TargetingState;
}

UPlayerAttackState* UPlayerStateMachine::GetAttackState() const
{
	return AttackState;
}

UPlayerDodgeState* UPlayerStateMachine::GetDodgeState() const
{
	return DodgeState;
}

UPlayerHitState* UPlayerStateMachine::GetHitState() const
{
	return HitState;
}

UPlayerThrowState* UPlayerStateMachine::GetThrowState() const
{
	return ThrowState;
}

UPlayerHealState* UPlayerStateMachine::GetHealState() const
{
	return HealState;
}

UPlayerDieState* UPlayerStateMachine::GetDieState() const
{
	return DieState;
}