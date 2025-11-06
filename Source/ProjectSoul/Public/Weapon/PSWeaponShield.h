#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSWeaponShield.generated.h"

UCLASS()
class PROJECTSOUL_API APSWeaponShield : public APSWeaponBase
{
	GENERATED_BODY()
	
public:
	APSWeaponShield();

	void StartBlock();
	void EndBlock();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shield")
	bool bIsBlocking;
};
