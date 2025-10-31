#include "Enemy/PSBossProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

APSBossProjectileBase::APSBossProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	if (MeshComp)
	{
		MeshComp->SetupAttachment(CollisionComp);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APSBossProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionComp)
	{
		CollisionComp->InitSphereRadius(15.f);
		CollisionComp->SetCollisionProfileName("BlockAllDynamic");
		CollisionComp->OnComponentHit.AddDynamic(this, &APSBossProjectileBase::OnHit);
		RootComponent = CollisionComp;
	}
	if (ProjectileMovement)
	{
		ProjectileMovement->UpdatedComponent = CollisionComp;
		ProjectileMovement->InitialSpeed = 400.f;
		ProjectileMovement->MaxSpeed = 8000.f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->ProjectileGravityScale = 0.f;
	}
}

void APSBossProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		if (!OtherActor->ActorHasTag("Player"))
		{
			return;
		}
		if (OtherActor->ActorHasTag("Enemy"))
		{
			return;
		}
		UGameplayStatics::ApplyDamage(
			OtherActor, 
			Damage, 
			nullptr, 
			this, 
			UDamageType::StaticClass());
		Destroy();
	}
}

void APSBossProjectileBase::SetHomingTarget(AActor* Target)
{
	if (ProjectileMovement && Target)
	{
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->HomingAccelerationMagnitude = 2000.f;
		ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
	}
}