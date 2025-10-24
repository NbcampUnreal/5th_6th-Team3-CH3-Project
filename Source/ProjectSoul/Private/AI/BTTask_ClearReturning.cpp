#include "AI/BTTask_ClearReturning.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearReturning::UBTTask_ClearReturning()
{
    NodeName = TEXT("Clear Investigating Flag");
}

EBTNodeResult::Type UBTTask_ClearReturning::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsBool("bIsReturning", false);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}