#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossSetState.generated.h"

UENUM(BlueprintType)
enum class EBossEnemyStateType : uint8
{
	Idle,
	Chase,
	Attack,
	Skill,
	Investigate,
	Return,
	Die,
	Hit
};


UCLASS()
class PROJECTSOUL_API UBTTask_BossSetState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossSetState();

protected:
	UPROPERTY(EditAnywhere, Category = "State")
	EBossEnemyStateType TargetState;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
