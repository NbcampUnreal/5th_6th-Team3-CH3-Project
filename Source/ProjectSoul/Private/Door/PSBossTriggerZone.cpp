#include "Door/PSBossTriggerZone.h"
#include "Components/BoxComponent.h"
#include "Door/PSBossRoomDoor.h"
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

}


void APSBossTriggerZone::BeginPlay()
{
	Super::BeginPlay();
	// 보스 바인딩
	
}

void APSBossTriggerZone::OnPlayerEnter(
	UPrimitiveComponent* OverlappingComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APSCharacter* Player = Cast<APSCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player entered Boss Room"));
		OnBossDefeated();

		/*if (BossDoor)
		{
			BossDoor->CloseDoor();
			BossDoor->SetLocked(true);
		}*/
	}
}

void APSBossTriggerZone::OnBossDefeated()
{
	if (BossDoor)
	{
		BossDoor->SetLocked(false);
		BossDoor->OpenDoor();
	}
}



