#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSWeaponSword.generated.h"


UCLASS()
class PROJECTSOUL_API APSWeaponSword : public APSWeaponBase
{
	GENERATED_BODY()

public:
	APSWeaponSword();

	virtual void Attack(AActor* Target) override;

	virtual void EnableWeaponCollision() override;

	virtual void DisableWeaponCollision() override;
};
