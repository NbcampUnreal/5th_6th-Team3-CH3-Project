#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTSOUL_API APSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APSWeaponBase();

    virtual void BeginPlay() override;

    virtual void Attack(AActor* Target);

    virtual void EnableWeaponCollision();

    virtual void DisableWeaponCollision();

    UFUNCTION()
    virtual void OnWeaponOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    UBoxComponent* WeaponCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    float AttackRange;

    UPROPERTY()
    TSet<AActor*> DamagedActors;
};
