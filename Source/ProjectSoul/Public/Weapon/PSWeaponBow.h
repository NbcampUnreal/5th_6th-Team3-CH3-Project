#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSWeaponBow.generated.h"

UCLASS()
class PROJECTSOUL_API APSWeaponBow : public APSWeaponBase
{
	GENERATED_BODY()

public:
	APSWeaponBow();

	virtual void Attack(AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Bow")
	TSubclassOf<AActor> ArrowProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Bow")
	float LaunchSpeed;
	
};
