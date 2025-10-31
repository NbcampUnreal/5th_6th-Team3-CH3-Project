#include "UI/PSTriggerActor.h"
#include "UI/PSPlayerHUDWidget.h"
#include "Components/BoxComponent.h"

APSTriggerActor::APSTriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BossTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BossTrigger"));
	SetRootComponent(BossTrigger);

	BossTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BossTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	BossTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APSTriggerActor::BeginPlay()
{
	BossTrigger->OnComponentBeginOverlap.AddDynamic(this, &APSTriggerActor::TriggerOn);
	BossTrigger->OnComponentEndOverlap.AddDynamic(this, &APSTriggerActor::TriggerOff);
}


void APSTriggerActor::TriggerOn(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
    UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	OnTrigger.Broadcast(true);
}

void APSTriggerActor::TriggerOff(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	OnTrigger.Broadcast(false);
}

