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

	//ĳ���� ���� �ڵ� �ۼ�
	Player->SetPlayerHealthStats(HealAmount);

	Destroy();

}


