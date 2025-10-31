#include "Enemy/PSEnemyAIController.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Enemy/PSEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

APSEnemyAIController::APSEnemyAIController()
	:AttackRange(200.0f),
	SkillAttackRange(400.0f)
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 100.0f;
	SightConfig->SetMaxAge(1.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 0.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void APSEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(TEXT("bCanSeeTarget"), false);
		BlackboardComp->SetValueAsBool(TEXT("bIsInvestigating"), false);
		BlackboardComp->SetValueAsBool(TEXT("bInAttackRange"), false);
		BlackboardComp->SetValueAsBool(TEXT("bIsReturning"), false);
		BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), false);
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector SpawnLocation = ControlledPawn->GetActorLocation();
			BlackboardComp->SetValueAsVector(TEXT("SpawnPointLocation"), ControlledPawn->GetActorLocation());
			BlackboardComp->SetValueAsRotator(TEXT("SpawnRotation"), ControlledPawn->GetActorRotation());
		}

		StartBehaviorTree();
	}

	if (AIPerception)
	{
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(
			this,
			&APSEnemyAIController::OnPerceptionUpdated
		);
	}
}

void APSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void APSEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Actor != PlayerPawn || !BlackboardComp)
	{
		return;
	}
	if (Stimulus.WasSuccessfullySensed())
	{
		BlackboardComp->SetValueAsObject(TEXT("TargetActor"), Actor);
		BlackboardComp->SetValueAsBool(TEXT("bCanSeeTarget"), true);
		BlackboardComp->SetValueAsBool(TEXT("bIsInvestigating"), false);
	}
	else
	{
		BlackboardComp->SetValueAsBool(TEXT("bCanSeeTarget"), false);
		BlackboardComp->SetValueAsBool(TEXT("bIsInvestigating"), true);
		BlackboardComp->SetValueAsVector(TEXT("TargetLastKnownLocation"), Actor->GetActorLocation());
		BlackboardComp->ClearValue(TEXT("TargetActor"));
	}
}

UBlackboardComponent* APSEnemyAIController::GetBlackboardComp() const
{
	return BlackboardComp;
}

void APSEnemyAIController::StartBehaviorTree()
{
	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

float APSEnemyAIController::GetAttackRange()
{
	return AttackRange;
}

float APSEnemyAIController::GetSkillAttackRange()
{
	return SkillAttackRange;
}