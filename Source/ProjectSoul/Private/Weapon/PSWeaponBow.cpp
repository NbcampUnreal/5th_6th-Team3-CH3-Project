#include "Weapon/PSWeaponBow.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/PSArrow.h"
#include "GameFramework/ProjectileMovementComponent.h"

APSWeaponBow::APSWeaponBow()
{
	ItemType = "Bow";
	AttackPower = 30.0f;
	LaunchSpeed = 1500.0f;
}

void APSWeaponBow::Attack(AActor* Target)
{
	Super::Attack(Target);

	if (!ArrowProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No projectile class set for Bow!"));
		return;
	}

	FVector SpawnLocation = StaticMesh->GetSocketLocation(FName("ArrowSoket"));
	FRotator SpawnRotation;

	if (Target)
	{
		SpawnRotation = (Target->GetActorLocation() - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = GetOwner()->GetActorRotation();
	}

	APSArrow* Arrow = GetWorld()->SpawnActor<APSArrow>(
		ArrowProjectileClass,
		SpawnLocation,
		SpawnRotation
	);

	if (Arrow)
	{
		if (UProjectileMovementComponent* MoveComp = Arrow->FindComponentByClass<UProjectileMovementComponent>())
		{
			MoveComp->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
			MoveComp->Activate();
		}

		Arrow->Damage = AttackPower;

		Arrow->SetOwner(this);
	}
}

