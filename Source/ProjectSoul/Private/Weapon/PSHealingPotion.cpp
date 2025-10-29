#include "Weapon/PSHealingPotion.h"
#include "Character/PSCharacter.h"

APSHealingPotion::APSHealingPotion()
	: HealAmount(20.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	if (Scene)
	{
		SetRootComponent(Scene);
	}
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(Scene);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //test
		StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}
void APSHealingPotion::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMesh)
	{
		StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &APSHealingPotion::OnPotionOverlap)
	}
}
void APSHealingPotion::OnPotionOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Healing Potion overlapped with: %s"), *OtherActor->GetName());
	
	APSCharacter* Player = Cast<APSCharacter>(OtherActor);
	if (Player)
	{
		UseItem(Player);
	}
	
}

void APSHealingPotion::UseItem(APSCharacter* Player)
{
	
	if (!Player)
	{
		return;
	}

	Player->SetPlayerHealthStats(HealAmount);

	Destroy();

}


