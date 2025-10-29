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
	}
}

void APSHealingPotion::UseItem(APSCharacter* Player)
{

	if (!Player)
	{
		return;
	}

	//캐릭터 힐링 코드 작성
	Player->SetPlayerHealthStats(HealAmount);

	Destroy();

}


