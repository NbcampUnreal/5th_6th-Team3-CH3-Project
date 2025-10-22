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

    virtual void Tick(float DeltaTime) override;
    virtual void Attack(AActor* Target);
    virtual void EnableWeaponCollision();
    virtual void DisableWeaponCollision();
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnWeaponOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    static float ApplyDamage(
        AActor* DamagedActor,
        float BaseDamage,
        AController* EventInstigator,
        AActor* DamageCauser,
        TSubclassOf<UDamageType> DamageTypeClass);

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Component")
    USceneComponent* Scene;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Component")
    UBoxComponent* WeaponCollision;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Component")
    UStaticMeshComponent* StaticMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName ItemType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float AttackPower;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float AttackRange;
    UPROPERTY()
    TSet<AActor*> DamagedActors;






	

};
