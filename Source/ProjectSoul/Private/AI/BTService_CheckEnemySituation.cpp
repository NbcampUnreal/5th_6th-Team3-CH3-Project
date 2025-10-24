#include "AI/BTService_CheckEnemySituation.h"
#include "Enemy/PSEnemyAIController.h"
#include "Kismet/GameplayStatics.h"

UBTService_CheckEnemySituation::UBTService_CheckEnemySituation()
{
    NodeName = TEXT("Check Enemy Situation");
    Interval = 0.2f;
}

void UBTService_CheckEnemySituation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController->GetPawn();
    AActor* Player = UGameplayStatics::GetPlayerPawn(Pawn->GetWorld(), 0);

    float Distance = FVector::Dist(Player->GetActorLocation(), Pawn->GetActorLocation());
    APSEnemyAIController* PSController = Cast<APSEnemyAIController>(AIController);
    if (!PSController) return;
    bool bInAttackRange = Distance <= 500.0f;;

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInAttackRange"), bInAttackRange);
}