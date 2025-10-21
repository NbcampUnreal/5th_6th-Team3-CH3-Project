#include "Character/PSCharacter.h"

APSCharacter::APSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

