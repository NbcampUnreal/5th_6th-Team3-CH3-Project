#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSBossProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class PROJECTSOUL_API APSBossProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APSBossProjectileBase();

	void SetHomingTarget(AActor* Target);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 30.f;
};
