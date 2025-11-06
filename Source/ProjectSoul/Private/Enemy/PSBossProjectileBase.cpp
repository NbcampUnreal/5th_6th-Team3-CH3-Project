#include "Enemy/PSBossProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

APSBossProjectileBase::APSBossProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	if (MeshComp)
	{
		MeshComp->SetupAttachment(CollisionComp);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void APSBossProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
		CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APSBossProjectileBase::OnProjectileOverlap);
		RootComponent = CollisionComp;
	}

	if (ProjectileMovement)
	{
		ProjectileMovement->UpdatedComponent = CollisionComp;
		ProjectileMovement->InitialSpeed = 250.f;
		ProjectileMovement->MaxSpeed = 1500.f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->ProjectileGravityScale = 0.f;
	}
}

void APSBossProjectileBase::OnProjectileOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}

	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			nullptr,
			this,
			UDamageType::StaticClass()
		);
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