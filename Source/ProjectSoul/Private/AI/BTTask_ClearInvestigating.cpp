#include "AI/BTTask_ClearInvestigating.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearInvestigating::UBTTask_ClearInvestigating()
{
    NodeName = TEXT("Clear Investigating Flag");
}

EBTNodeResult::Type UBTTask_ClearInvestigating::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsBool("bIsInvestigating", false);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}