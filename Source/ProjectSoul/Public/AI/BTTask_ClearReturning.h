#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearReturning.generated.h"

UCLASS()
class PROJECTSOUL_API UBTTask_ClearReturning : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ClearReturning();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
