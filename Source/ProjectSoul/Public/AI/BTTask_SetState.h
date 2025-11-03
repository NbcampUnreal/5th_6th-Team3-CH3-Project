#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetState.generated.h"

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	Idle,
	Chase,
	Attack,
	Investigate,
	Return,
	Die,
	Hit
};

UCLASS()
class PROJECTSOUL_API UBTTask_SetState : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetState();

protected:
	UPROPERTY(EditAnywhere, Category = "State")
	EEnemyStateType TargetState;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
