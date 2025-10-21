#include "StateMachine/PlayerStateMachine.h"
#include "Character/PSCharacter.h"
#include "State/PlayerFreeLookState.h"
#include "State/PlayerTargetingState.h"

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
