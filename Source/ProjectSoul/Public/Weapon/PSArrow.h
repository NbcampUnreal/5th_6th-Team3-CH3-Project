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
	
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Arrow")
	float Damage;

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Weapon|Arrow")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Arrow")
	UProjectileMovementComponent* ProjectileMovement;



};
