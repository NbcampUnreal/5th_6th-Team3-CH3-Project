#include "Weapon/PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

APSWeaponBase::APSWeaponBase() :
    ItemType("Weapon"),
    AttackRange(0.0f),
    AttackPower(0.0f)
{
	PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    if (Scene)
    {
        SetRootComponent(Scene);
    }

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    if (StaticMesh)
    {
        StaticMesh->SetupAttachment(Scene);
        StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
    }

    WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
    if (WeaponCollision)
    {
        WeaponCollision->SetupAttachment(StaticMesh);
        WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore); 
        WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    }
}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

    WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APSWeaponBase::OnWeaponOverlap);
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

    UGameplayStatics::ApplyDamage(
        OtherActor,
        AttackPower,
        nullptr,
        this,
        UDamageType::StaticClass()
    );

    UE_LOG(LogTemp, Warning, TEXT("%s Damaged: %f"), *OtherActor->GetName(), AttackPower);
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