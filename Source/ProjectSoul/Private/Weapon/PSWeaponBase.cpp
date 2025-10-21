#include "Weapon/PSWeaponBase.h"

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APSWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

