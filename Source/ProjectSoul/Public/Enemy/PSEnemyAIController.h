#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PSEnemyAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class PROJECTSOUL_API APSEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	APSEnemyAIController();

	void SetSightAngle(float NewAngle);

	void StartBehaviorTree();

	float GetAttackRange();

	float GetSkillAttackRange();

	UBlackboardComponent* GetBlackboardComp() const;

	UAIPerceptionComponent* GetAIPerception() const;

	UAISenseConfig_Sight* GetSightConfig() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float SkillAttackRange;
};
