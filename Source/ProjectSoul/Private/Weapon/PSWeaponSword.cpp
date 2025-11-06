#include "Weapon/PSWeaponSword.h"
#include "Kismet/GameplayStatics.h"

APSWeaponSword::APSWeaponSword()
{
	ItemType = "Sword";
	AttackPower = 30.0f;
	AttackRange = 120.0f;
}

void APSWeaponSword::EnableWeaponCollision()
{
	Super::EnableWeaponCollision();
}

void APSWeaponSword::DisableWeaponCollision()
{
	Super::DisableWeaponCollision();
}
