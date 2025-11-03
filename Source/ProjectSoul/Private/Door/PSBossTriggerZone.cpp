#include "Door/PSBossTriggerZone.h"
#include "Components/BoxComponent.h"
#include "Door/PSBossRoomDoor.h"
#include "Enemy/PSBossEnemy.h"
#include "Character/PSCharacter.h"


APSBossTriggerZone::APSBossTriggerZone()
{
 
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	if (TriggerBox)
	{
		SetRootComponent(TriggerBox);
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APSBossTriggerZone::OnPlayerEnter);
	}

	bBossDefeated = false;
}


void APSBossTriggerZone::BeginPlay()
{
	Super::BeginPlay();

	if (BossActor)
	{
		APSBossEnemy* Boss = Cast<APSBossEnemy>(BossActor);
		if (Boss)
		{
			Boss->OnBossDefeated.AddDynamic(this, &APSBossTriggerZone::OnBossDefeated);
		}
	}

	if (bBossDefeated)
	{
		if (BossDoor)
		{
			BossDoor->SetLocked(false);
			BossDoor->OpenDoor();
		}
	}
	
}

void APSBossTriggerZone::OnPlayerEnter(
	UPrimitiveComponent* OverlappingComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APSCharacter* Player = Cast<APSCharacter>(OtherActor))
	{
		if (BossDoor && !bBossDefeated)
		{
			BossDoor->CloseDoor();
			BossDoor->SetLocked(true);
		}
	}
}

void APSBossTriggerZone::OnBossDefeated()
{
	if (BossDoor)
	{
		OpenDoor();
		bBossDefeated = true;
	}
}

void APSBossTriggerZone::OpenDoor()
{
	BossDoor->SetLocked(false);
	BossDoor->OpenDoor();
}





