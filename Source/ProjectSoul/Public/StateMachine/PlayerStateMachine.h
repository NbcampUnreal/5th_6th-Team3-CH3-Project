#pragma once

#include "CoreMinimal.h"
#include "StateMachine/StateMachineBase.h"
#include "PlayerStateMachine.generated.h"

class UPlayerStateBase;
class UPlayerFreeLookState;
class UPlayerTargetingState;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPlayerStateMachine : public UStateMachineBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(ACharacter* InOwner) override;

	virtual void OnUpdate(float DeltaTime) override;

	UPlayerStateBase* GetCurrentState() const;

	APSCharacter* GetOwnerCharacter() const;

	UPlayerFreeLookState* GetFreeLookState() const;

	UPlayerTargetingState* GetTargetingState() const;

protected:
	UPROPERTY()
	TObjectPtr<UPlayerFreeLookState> FreeLookState;

	UPROPERTY()
	TObjectPtr <UPlayerTargetingState> TargetingState;
};
