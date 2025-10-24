#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSEnemy.generated.h"

class UEnemyStateMachine;

UCLASS()
class PROJECTSOUL_API APSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	APSEnemy();
	virtual void SetMovementSpeed(float NewSpeed);

	virtual TObjectPtr<UEnemyStateMachine> GetStateMachine();

protected:
	virtual void BeginPlay() override;

public:	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UEnemyStateMachine> StateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float RunSpeed;
private:

};
