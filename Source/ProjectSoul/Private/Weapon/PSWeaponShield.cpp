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
	UE_LOG(LogTemp, Warning, TEXT("Blocking Started"));
}

void APSWeaponShield::EndBlock()
{
	bIsBlocking = false;
	UE_LOG(LogTemp, Warning, TEXT("Blocking Ended"));
}
