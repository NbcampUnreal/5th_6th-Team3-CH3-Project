#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSWeaponBase.generated.h"

class UBoxComponent;
class USoundBase;

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

    USoundBase* GetAttackSound() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    UBoxComponent* WeaponCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Component")
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Sword")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Sword")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shield")
    float DefensePower;

    UPROPERTY()
    TSet<AActor*> DamagedActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Sound")
	TObjectPtr<USoundBase> AttackSound;
};
