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

    bool bIsAttacking = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bIsAttacking"));
    if (bIsAttacking)
    {
        return;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController->GetPawn();
    AActor* Player = UGameplayStatics::GetPlayerPawn(Pawn->GetWorld(), 0);

    APSEnemyAIController* EnemyAIController = Cast<APSEnemyAIController>(AIController);
    if (!EnemyAIController)
    {
        return;
    }

    float Distance = FVector::Dist(Player->GetActorLocation(), Pawn->GetActorLocation());
    bool bInAttackRange = Distance <= EnemyAIController->GetAttackRange();
    bool bInSkillRange = Distance <= EnemyAIController->GetSkillAttackRange();
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInAttackRange"), bInAttackRange);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInSkillRange"), bInSkillRange);
}