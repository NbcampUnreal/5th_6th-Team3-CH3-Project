#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSCharacter.generated.h"

UCLASS()
class PROJECTSOUL_API APSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
