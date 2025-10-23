#include "Weapon/PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
    WeaponCollision->SetupAttachment(Scene);
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore); 
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMesh->SetupAttachment(WeaponCollision);
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 

    AttackRange = 90.0f;
    AttackPower = 10.0f;

}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APSWeaponBase::OnWeaponOverlap);
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
    if (!OtherActor || OtherActor == GetOwner()) 
    {
        return;
    }

    if (DamagedActors.Contains(OtherActor)) 
    {
        return;
    }

    if (!OtherActor->ActorHasTag("Enemy"))
    {
        return;
    }

    DamagedActors.Add(OtherActor); 

    ApplyDamage(
        OtherActor,
        AttackPower,
        GetOwner()->GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );

    UE_LOG(LogTemp, Log, TEXT("%s hit %s"), *GetName(), *OtherActor->GetName());
}

// Deliver damage to target
float APSWeaponBase::ApplyDamage(
    AActor* DamagedActor,
    float BaseDamage,
    AController* EventInstigator,
    AActor* DamageCauser,
    TSubclassOf<UDamageType> DamageTypeClass)
{
    return UGameplayStatics::ApplyDamage(DamagedActor, BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);
}

void APSWeaponBase::EnableWeaponCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
}

void APSWeaponBase::DisableWeaponCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DamagedActors.Empty(); // Initialize the list
}

void APSWeaponBase::Attack(AActor* Target)
{
    
}



