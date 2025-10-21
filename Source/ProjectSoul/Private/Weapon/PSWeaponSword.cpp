#include "Weapon/PSWeaponSword.h"
#include "Kismet/GameplayStatics.h"

APSWeaponSword::APSWeaponSword()
{
	ItemType = "Sword";
	AttackPower = 30.0f;
	AttackRange = 120.0f;
}

void APSWeaponSword::Attack(AActor* Target)
{
	//콜리전 활성화 함수
	Super::Attack(Target);

	UE_LOG(LogTemp, Log, TEXT("Sword swing at %s"), *Target->GetName());


	if (Target)
	{
		ApplyDamage(Target, AttackPower, nullptr, this, nullptr);
	}

}

void APSWeaponSword::EnableWeaponCollision()
{
	Super::EnableWeaponCollision();
	UE_LOG(LogTemp, Log, TEXT("Sword collision enabled"));

}

void APSWeaponSword::DisableWeaponCollision()
{
	Super::DisableWeaponCollision();
	UE_LOG(LogTemp, Log, TEXT("Sword collision disabled"));

}
