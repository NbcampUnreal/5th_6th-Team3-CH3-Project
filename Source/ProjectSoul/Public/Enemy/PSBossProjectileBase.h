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

	UFUNCTION()
	void OnProjectileOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void SetHomingTarget(AActor* Target);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 5.f;
};
