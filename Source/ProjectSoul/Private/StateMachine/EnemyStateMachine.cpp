#include "StateMachine/EnemyStateMachine.h"
#include "State/EnemyHitState.h"
#include "Enemy/PSEnemy.h"
#include "State/EnemyAttackState.h"
#include "State/EnemyChaseState.h"
#include "State/EnemyDieState.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyInvestigateState.h"
#include "State/EnemyReturnState.h"

void UEnemyStateMachine::Initialize(ACharacter* InOwner)
{
	Super::Initialize(InOwner);

	IdleState = NewObject<UEnemyIdleState>(this);
	if (IdleState)
	{
		IdleState->Initialize(this);
	}

	AttackState = NewObject<UEnemyAttackState>(this);
	if (AttackState)
	{
		AttackState->Initialize(this);
	}

	ChaseState = NewObject<UEnemyChaseState>(this);
	if (ChaseState)
	{
		ChaseState->Initialize(this);
	}

	DieState = NewObject<UEnemyDieState>(this);
	if (DieState)
	{
		DieState->Initialize(this);
	}

	InvestigateState = NewObject<UEnemyInvestigateState>(this);
	if (InvestigateState)
	{
		InvestigateState->Initialize(this);
	}

	ReturnState = NewObject<UEnemyReturnState>(this);
	if (ReturnState)
	{
		ReturnState->Initialize(this);
	}

	HitState= NewObject<UEnemyHitState>(this);
	if (HitState)
	{
		HitState->Initialize(this);
	}

	CurrentState = IdleState;
	if (CurrentState)
	{
		CurrentState->OnEnter();
	}
}

void UEnemyStateMachine::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
}

void UEnemyStateMachine::ChangeState(UStateBase* NewState)
{
	if (CurrentState && CurrentState->IsA(UEnemyHitState::StaticClass()))
	{
		ACharacter* Enemy = this->GetOwnerCharacter();
		if (Enemy)
		{
			UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
			UAnimMontage* Montage = Cast<APSEnemy>(Enemy)->GetHitMontage();
			if (Anim && Anim->Montage_IsPlaying(Montage))
			{
				UE_LOG(LogTemp, Warning, TEXT("Blocked: Hit montage still playing."));
				return;
			}
		}
	}
	if (!NewState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null state."));
		return;
	}

	if (NewState->IsA(UEnemyHitState::StaticClass()))
	{
		if (CurrentState)
		{
			CurrentState->OnExit(); 
		}

		CurrentState = NewState;
		CurrentState->OnEnter();    
		return;
	}

	if (NewState == CurrentState && NewState->IsA(UEnemyHitState::StaticClass()))
	{
		CurrentState->OnExit();
		CurrentState->OnEnter();
		return;
	}

	if (NewState == CurrentState)
	{
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


UEnemyStateBase* UEnemyStateMachine::GetCurrentState() const
{
	return Cast<UEnemyStateBase>(CurrentState);
}

UEnemyChaseState* UEnemyStateMachine::GetChaseState() const 
{
	return ChaseState;
}

UEnemyAttackState* UEnemyStateMachine::GetAttackState() const
{
	return AttackState;
}

UEnemyDieState* UEnemyStateMachine::GetDieState() const
{
	return DieState;
}

UEnemyIdleState* UEnemyStateMachine::GetIdleState() const
{
	return IdleState;
}

UEnemyInvestigateState* UEnemyStateMachine::GetInvestigateState() const
{
	return InvestigateState;
}

UEnemyReturnState* UEnemyStateMachine::GetReturnState() const
{
	return ReturnState;
}

UEnemyHitState* UEnemyStateMachine::GetHitState() const
{
	return HitState;
}
