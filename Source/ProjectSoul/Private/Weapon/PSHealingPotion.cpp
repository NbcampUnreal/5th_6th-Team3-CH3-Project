#include "Weapon/PSHealingPotion.h"
#include "Character/PSCharacter.h"
#include "Structs/FPlayerStats.h" 
#include "Structs/FStat.h"

APSHealingPotion::APSHealingPotion()
{
 
	PrimaryActorTick.bCanEverTick = false;



}

void APSHealingPotion::UseItem(AActor* TargetActor)
{
	if (!TargetActor)
	{
		return;
	}

	APSCharacter* Player = Cast<APSCharacter>(TargetActor);

	if (!Player)
	{
		return;
	}

	//ĳ���� ���� �ڵ� �ۼ�
}


