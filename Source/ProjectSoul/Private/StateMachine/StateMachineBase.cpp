#include "StateMachine/StateMachineBase.h"
#include "State/StateBase.h"

void UStateMachineBase::Initialize(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	CurrentState = nullptr;
}

void UStateMachineBase::OnUpdate(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->OnUpdate(DeltaTime);
	}
}

void UStateMachineBase::ChangeState(UStateBase* NewState)
{
	if (!NewState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null state."));
		return;
	}

	if (NewState == CurrentState)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Change to same state."));
		return;
	}

	if (CurrentState)
	{
		CurrentState->OnExit();
	}

	CurrentState = NewState;

	if (CurrentState)
	{
		CurrentState->OnEnter();
	}
}

UStateBase* UStateMachineBase::GetCurrentState() const
{
	return CurrentState;
}

ACharacter* UStateMachineBase::GetOwnerCharacter() const
{
	return OwnerCharacter;
}
