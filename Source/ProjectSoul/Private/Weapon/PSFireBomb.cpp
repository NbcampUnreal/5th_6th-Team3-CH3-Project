#include "Weapon/PSFireBomb.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APSFireBomb::APSFireBomb() :
	FireBombDamage(30.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		SetRootComponent(StaticMesh);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	FireBombCollision = CreateDefaultSubobject<USphereComponent>(TEXT("FireBombCollision"));
	if (FireBombCollision)
	{
		FireBombCollision->SetupAttachment(StaticMesh);
		FireBombCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		FireBombCollision->OnComponentHit.AddDynamic(this, &APSFireBomb::OnHit);
	}
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = 1500.0f;
		ProjectileMovement->MaxSpeed = 1500.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->ProjectileGravityScale = 1.0f; //Gravity
	}

}

void APSFireBomb::BeginPlay()
{
	Super::BeginPlay();
}

void APSFireBomb::OnHit(
	UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamage(
		this,
		FireBombDamage,
		GetActorLocation(),
		BombRadius,
		DamageType,
		IgnoreActors,
		this,
		GetInstigatorController(),
		true
	);

	Destroy();
}

