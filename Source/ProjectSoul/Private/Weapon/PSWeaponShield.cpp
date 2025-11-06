#include "Weapon/PSWeaponShield.h"

APSWeaponShield::APSWeaponShield()
{
	ItemType = "Shield";
	DefensePower = 20.0f;
	bIsBlocking = false;
}

void APSWeaponShield::StartBlock()
{
	bIsBlocking = true;
}

void APSWeaponShield::EndBlock()
{
	bIsBlocking = false;
}
