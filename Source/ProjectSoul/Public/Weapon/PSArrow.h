#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSArrow.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PROJECTSOUL_API APSArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSArrow();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Weapon|Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Arrow")
	float Damage;

	UPROPERTY()
	TSet<AActor*> DamagedActors;

};
