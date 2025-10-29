#include "Weapon/PSFireBomb.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"

APSFireBomb::APSFireBomb() :
	FireBombDamage(30.0f),
	BombRadius(30.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	FireBombCollision = CreateDefaultSubobject<USphereComponent>(TEXT("FireBombCollision"));
	if (FireBombCollision)
	{
		SetRootComponent(FireBombCollision);
		FireBombCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		FireBombCollision->OnComponentHit.AddDynamic(this, &APSFireBomb::OnHit);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(FireBombCollision);
		
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	UE_LOG(LogTemp, Warning, TEXT("On hit"));


	if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
	{
		return;
	}

	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f),
			true
		);
	}

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamage(
		this,
		FireBombDamage,
		GetActorLocation(),
		BombRadius,
		UDamageType::StaticClass(),
		IgnoreActors,
		this,
		GetWorld()->GetFirstPlayerController(),
		true
	);

	Destroy();
}

