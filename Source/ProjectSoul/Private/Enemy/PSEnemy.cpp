#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
APSEnemy::APSEnemy()
	: HP(100), 
	Attack(20), 
	Score(50),
	WalkSpeed(300.0f),
	RunSpeed(600.0f)
{
	AIControllerClass = APSEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	UCharacterMovementComponent* EnemyMovement = GetCharacterMovement();
	EnemyMovement->MaxWalkSpeed = WalkSpeed;
	EnemyMovement->bOrientRotationToMovement = true;
	EnemyMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void APSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}
void APSEnemy::SetMovementSpeed(float NewSpeed)
{
	if (UCharacterMovementComponent* EnemyMovement = GetCharacterMovement())
	{
		EnemyMovement->MaxWalkSpeed = NewSpeed;
	}
}