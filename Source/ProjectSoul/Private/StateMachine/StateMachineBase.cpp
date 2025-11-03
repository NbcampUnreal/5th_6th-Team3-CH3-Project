#include "StateMachine/StateMachineBase.h"
#include "State/StateBase.h"
#include "State/PlayerAttackState.h"

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
		if (NewState->IsA(UPlayerAttackState::StaticClass()))
		{
			// Pass
		}
		else
		{
			return;
		}
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
