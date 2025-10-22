#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSEnemy.generated.h"

UCLASS()
class PROJECTSOUL_API APSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	APSEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;

public:	
protected:
private:
	int32 HP;
	int32 Attack;
	int32 Score;

};
