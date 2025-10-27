#include "Weapon/PSArrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


APSArrow::APSArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);
	StaticMeshComp->SetNotifyRigidBodyCollision(true);
	StaticMeshComp->SetCollisionProfileName("BlockAllDynamic");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;

}

void APSArrow::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMeshComp && !StaticMeshComp->OnComponentHit.IsBound())
	{
		StaticMeshComp->OnComponentHit.AddDynamic(this, &APSArrow::OnHit);
	}
}

void APSArrow::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Arrow hit: %s"), OtherActor ? *OtherActor->GetName() : TEXT("None"));

	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
		Destroy();
	}
}




