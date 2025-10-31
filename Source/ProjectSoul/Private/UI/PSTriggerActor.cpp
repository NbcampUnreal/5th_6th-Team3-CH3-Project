#include "UI/PSTriggerActor.h"
#include "UI/PSPlayerHUDWidget.h"
#include "Enemy/PSEnemy.h"
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
	BossTrigger->GetOverlappingActors(TriggerOnMonsters, APSEnemy::StaticClass());
	if (TriggerOnMonsters.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TriggerActor : Find Monster"));
		OnTrigger.Broadcast(TriggerOnMonsters[0], true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TriggerActor : Not Find Monster"));
	}
}

void APSTriggerActor::TriggerOff(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	for (int i = 0; i < TriggerOnMonsters.Num(); i++)
	{
		TriggerOnMonsters[i] = nullptr;
	}
	OnTrigger.Broadcast(nullptr, false);
}

