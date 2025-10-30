#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSTriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrigger);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrigger, AActor*, Monster, float, Damage);

class UBoxComponent;

UCLASS()
class PROJECTSOUL_API APSTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APSTriggerActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnTrigger OnTrigger;

private:
	UFUNCTION()
	void TriggerOn(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Tirgger")
	UBoxComponent* BossTrigger;

};
