#pragma once

#include "CoreMinimal.h"
#include "StateMachine/StateMachineBase.h"
#include "PlayerStateMachine.generated.h"

class UPlayerStateBase;
class UPlayerFreeLookState;
class UPlayerTargetingState;
class UPlayerAttackState;
class UPlayerDodgeState;
class UPlayerHitState;
class UPlayerThrowState;
class UPlayerHealState;
class UPlayerDieState;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPlayerStateMachine : public UStateMachineBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(ACharacter* InOwner) override;

	virtual void OnUpdate(float DeltaTime) override;

	UPlayerStateBase* GetCurrentState() const;

	UPlayerStateBase* GetPrevState() const;

	void SetPrevState(UPlayerStateBase* NewPrevState);

	APSCharacter* GetOwnerCharacter() const;

	UPlayerFreeLookState* GetFreeLookState() const;

	UPlayerTargetingState* GetTargetingState() const;

	UPlayerAttackState* GetAttackState() const;

	UPlayerDodgeState* GetDodgeState() const;

	UPlayerHitState* GetHitState() const;

	UPlayerThrowState* GetThrowState() const;

	UPlayerHealState* GetHealState() const;

	UPlayerDieState* GetDieState() const;

protected:
	UPROPERTY()
	TObjectPtr<UPlayerFreeLookState> FreeLookState;

	UPROPERTY()
	TObjectPtr <UPlayerTargetingState> TargetingState;

	UPROPERTY()
	TObjectPtr <UPlayerAttackState> AttackState;

	UPROPERTY()
	TObjectPtr <UPlayerDodgeState> DodgeState;

	UPROPERTY()
	TObjectPtr <UPlayerHitState> HitState;

	UPROPERTY()
	TObjectPtr <UPlayerThrowState> ThrowState;

	UPROPERTY()
	TObjectPtr <UPlayerHealState> HealState;

	UPROPERTY()
	TObjectPtr <UPlayerDieState> DieState;

private:
	UPROPERTY()
	TObjectPtr<UPlayerStateBase> PrevState;
};
