#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSArrow.generated.h"

UCLASS()
class PROJECTSOUL_API APSArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSArrow();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
