#include "Enemy/PSEnemy.h"

APSEnemy::APSEnemy()
	: HP(100), Attack(20), Score(50)
{
	PrimaryActorTick.bCanEverTick = true;

}

void APSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void APSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APSEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

