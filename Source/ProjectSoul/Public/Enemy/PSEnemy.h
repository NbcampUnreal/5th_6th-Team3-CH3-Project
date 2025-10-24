#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs/FEnemyStats.h"
#include "PSEnemy.generated.h"

class UEnemyStateMachine;
class UWidgetComponent;

UCLASS()
class PROJECTSOUL_API APSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	APSEnemy();

	virtual void SetMovementSpeed(float NewSpeed);

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	virtual void BeginPlay() override;
	
private:
	void UpdateHealthWidget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UEnemyStateMachine> StateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FEnemyStats EnemyStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float RunSpeed;

private:

};
