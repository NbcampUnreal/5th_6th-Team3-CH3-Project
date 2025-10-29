#include "Weapon/PSHealingPotion.h"
#include "Character/PSCharacter.h"
#include "Components/BoxComponent.h"

APSHealingPotion::APSHealingPotion()
	: HealAmount(20.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
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

	PotionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	if (PotionCollision)
	{
		PotionCollision->SetupAttachment(StaticMesh);
		PotionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PotionCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
		PotionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}
void APSHealingPotion::BeginPlay()
{
	Super::BeginPlay();

	if (PotionCollision)
	{
		PotionCollision->OnComponentBeginOverlap.AddDynamic(this, &APSHealingPotion::OnPotionOverlap);
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
	UE_LOG(LogTemp, Log, TEXT("Healing Potion overlap"));
	
	APSCharacter* Player = Cast<APSCharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Healing Potion cast"));
		UseItem(Player);
	}
	
}

void APSHealingPotion::UseItem(APSCharacter* Player)
{
	UE_LOG(LogTemp, Log, TEXT("Healing Potion UseItem"));
	if (!Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Healing Potion return"));
		return;
	}

	Player->Heal(HealAmount);

	Destroy();

}



