#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateBase.generated.h"

class UStateMachineBase;

UCLASS()
class PROJECTSOUL_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UStateMachineBase* NewStateMachine);

	virtual void OnEnter();

	virtual void OnUpdate(float DeltaTime);

	virtual void OnExit();

protected:
	UPROPERTY()
	TObjectPtr<UStateMachineBase> StateMachine;
};
