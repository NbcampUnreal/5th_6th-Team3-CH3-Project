#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachineBase.generated.h"

class UStateBase;

UCLASS()
class PROJECTSOUL_API UStateMachineBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacter* InOwner);

	virtual void OnUpdate(float DeltaTime);

	void ChangeState(UStateBase* NewState);

	UStateBase* GetCurrentState() const;

	ACharacter* GetOwnerCharacter() const;

protected:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UStateBase> CurrentState;
};
