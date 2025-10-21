#include "Weapon/PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"

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

void APSWeaponBase::OnWeaponOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        ApplyDamage(OtherActor, AttackPower, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
    }
}

void APSWeaponBase::EnableWeaponCollision()
{
    
}

void APSWeaponBase::DisableWeaponCollision()
{

}

// 데미지 전달 함수
float APSWeaponBase::ApplyDamage(
    AActor* DamagedActor,
    float BaseDamage,
    AController* EventInstigator,
    AActor* DamageCauser,
    TSubclassOf<UDamageType> DamageTypeClass)
{
    return UGameplayStatics::ApplyDamage(DamagedActor, BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);
}

