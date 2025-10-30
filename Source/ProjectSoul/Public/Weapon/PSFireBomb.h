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
		UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	USphereComponent* FireBombCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|FireBomb")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Effects")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Effects")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|FireBomb")
	float FireBombDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|FireBomb")
	float BombRadius;

};
