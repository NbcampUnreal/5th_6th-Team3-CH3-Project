#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSWeaponBase.generated.h"

UCLASS()
class PROJECTSOUL_API APSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	APSWeaponBase();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float AttackPower;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float AttackRange;

    UFUNCTION()
    virtual void OnWeaponOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    virtual void EnableWeaponCollision();
    virtual void DisableWeaponCollision();

    // 데미지 전달 함수
    static float ApplyDamage(
        AActor* DamagedActor,
        float BaseDamage,
        AController* EventInstigator,
        AActor* DamageCauser,
        TSubclassOf<UDamageType> DamageTypeClass);

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;


	

};
