#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearInvestigating.generated.h"

UCLASS()
class PROJECTSOUL_API UBTTask_ClearInvestigating : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ClearInvestigating();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
