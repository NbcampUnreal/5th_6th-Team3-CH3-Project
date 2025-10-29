#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSHealingPotion.generated.h"

class APSCharacter;
class UBoxComponent;
struct FPlayerStats;


UCLASS()
class PROJECTSOUL_API APSHealingPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSHealingPotion();

	virtual void BeginPlay() override;//test

	UFUNCTION(BlueprintCallable, Category = "Item|Healing")
	void UseItem(APSCharacter* Player);

	UFUNCTION() //test
		void OnPotionOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UBoxComponent* PotionCollision;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item|Healing")
	float HealAmount;


};
