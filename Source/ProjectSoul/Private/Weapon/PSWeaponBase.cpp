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
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); //콜리전 기본 상태 : 꺼짐
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 충돌 무시
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // 캐릭터 ( Pawn과는 오버랩 허용 )

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMesh->SetupAttachment(WeaponCollision);

    AttackRange = 90.0f;
    AttackPower = 10.0f;

}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APSWeaponBase::OnWeaponOverlap); // 오버랩시 함수 실행
	
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
    if (!OtherActor || OtherActor == GetOwner()) //유효한 액터가 아니라면 무시
    {
        return;
    }

    if (DamagedActors.Contains(OtherActor)) //이미 맞은 적 무시 
    {
        return;
    }

    DamagedActors.Add(OtherActor); // 처음 맞은적 데미지 처리
    ApplyDamage(
        OtherActor,
        AttackPower,
        GetOwner()->GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );

    UE_LOG(LogTemp, Log, TEXT("%s hit %s"), *GetName(), *OtherActor->GetName());
}

// 타겟에게 데미지 전달
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
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //오버랩 여부 감지
}

void APSWeaponBase::DisableWeaponCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DamagedActors.Empty(); // 공격후 맞은적 초기화

}

void APSWeaponBase::Attack(AActor* Target)
{
    //자식클래스 구현
}

