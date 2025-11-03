#include "Door/PSBossRoomDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


APSBossRoomDoor::APSBossRoomDoor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	if (Scene)
	{
		SetRootComponent(Scene);
	}

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	if (LeftDoor)
	{
		LeftDoor->SetupAttachment(Scene);
	}

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	if (RightDoor)
	{
		RightDoor->SetupAttachment(Scene);
	}

	DoorBlocker = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBlocker"));
	if (DoorBlocker)
	{
		DoorBlocker->SetupAttachment(Scene);
		DoorBlocker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DoorBlocker->SetCollisionResponseToAllChannels(ECR_Block);
	}

	bIsLocked = false;
}

void APSBossRoomDoor::BeginPlay()
{
	Super::BeginPlay();

	//문 회전 로직
	LeftClosedRot = LeftDoor->GetRelativeRotation();
	RightClosedRot = RightDoor->GetRelativeRotation();

	LeftOpenRot = LeftClosedRot + FRotator(0.0f, -90.0f, 0.0f);
	RightOpenRot = RightClosedRot + FRotator(0.0f, 90.0f, 0.0f);

}

void APSBossRoomDoor::OpenDoor()
{
	if (bIsLocked) //잠겨 있다면
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Door Open"));
	LeftDoor->SetRelativeRotation(LeftOpenRot);
	RightDoor->SetRelativeRotation(RightOpenRot);

	DoorBlocker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APSBossRoomDoor::CloseDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door Close"));
	LeftDoor->SetRelativeRotation(LeftClosedRot);
	RightDoor->SetRelativeRotation(RightClosedRot);

	DoorBlocker->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APSBossRoomDoor::SetLocked(bool bLocked)
{
	bIsLocked = bLocked;

	DoorBlocker->SetCollisionEnabled(bIsLocked ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

bool APSBossRoomDoor::GetLocked()const
{
	return bIsLocked;
}




