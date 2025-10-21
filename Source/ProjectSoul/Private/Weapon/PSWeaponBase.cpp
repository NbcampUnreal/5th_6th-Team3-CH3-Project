#include "Weapon/PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    WeaponCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollision"));
    WeaponCollision->SetupAttachment(Scene);
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�ݸ��� �⺻ ���� : ����
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore); // ��� �浹 ����
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // ĳ���� ( Pawn���� ������ ��� )

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMesh->SetupAttachment(WeaponCollision);

    AttackRange = 90.0f;
    AttackPower = 10.0f;

}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APSWeaponBase::OnWeaponOverlap); // �������� �Լ� ����
	
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
        DisableWeaponCollision(); //�ѹ��� ����
    }
}

// Ÿ�ٿ��� ������ ����
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
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //������ ���� ����
}

void APSWeaponBase::DisableWeaponCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void APSWeaponBase::Attack(AActor* Target)
{
    //�ڽ�Ŭ���� ����
}

