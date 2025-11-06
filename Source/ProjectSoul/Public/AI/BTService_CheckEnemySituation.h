#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckEnemySituation.generated.h"

UCLASS()
class PROJECTSOUL_API UBTService_CheckEnemySituation : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckEnemySituation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
