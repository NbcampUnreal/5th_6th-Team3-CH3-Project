#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSFireBomb.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTSOUL_API APSFireBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	APSFireBomb();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	void Init(const FVector& Direction);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	TObjectPtr<USphereComponent> FireBombCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Effects")
	TObjectPtr<UParticleSystem> ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Effects")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|FireBomb")
	float FireBombDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|FireBomb")
	float BombRadius;
};
