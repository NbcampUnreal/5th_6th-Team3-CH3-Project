#include "State/StateBase.h"
#include "StateMachine/StateMachineBase.h"

void UStateBase::Initialize(UStateMachineBase* NewStateMachine)
{
	StateMachine = NewStateMachine;
}

void UStateBase::OnEnter()
{
}

void UStateBase::OnUpdate(float DeltaTime)
{
}

void UStateBase::OnExit()
{
}