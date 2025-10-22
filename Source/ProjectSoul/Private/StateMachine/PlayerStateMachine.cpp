#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerDodgeState.h"

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

	CurrentState = FreeLookState;
	if (CurrentState)
	{
		CurrentState->OnEnter();
	}

	UE_LOG(LogTemp, Log, TEXT("PlayerStateMachine Initialized"));
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
