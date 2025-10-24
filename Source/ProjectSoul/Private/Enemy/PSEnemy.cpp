#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "UI/PSMonsterWidget.h"

APSEnemy::APSEnemy()
	: Attack(20), 
	Score(50),
	WalkSpeed(300.0f),
	RunSpeed(600.0f)
{
	AIControllerClass = APSEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	if (HealthWidget)
	{
		HealthWidget->SetupAttachment(GetMesh());
		HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}

	UCharacterMovementComponent* EnemyMovement = GetCharacterMovement();
	EnemyMovement->MaxWalkSpeed = WalkSpeed;
	EnemyMovement->bOrientRotationToMovement = true;

	EnemyStats.Health = FStat();
	EnemyStats.Stamina = FStat();
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

float APSEnemy::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	EnemyStats.Health.AdjustValue(-DamageAmount);
	UpdateHealthWidget();

	UE_LOG(LogTemp, Warning, TEXT("Enemy take damage %.0f from %s"), DamageAmount, *DamageCauser->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Enemy Remain Health: %.0f / %.0f"), EnemyStats.Health.GetCurrent(), EnemyStats.Health.GetMax());

	if (EnemyStats.Health.IsZero())
	{
		Destroy();
		// Death
	}

	return ActualDamage;
}

void APSEnemy::UpdateHealthWidget()
{
	if (HealthWidget)
	{
		if (UUserWidget* Widget = HealthWidget->GetUserWidgetObject())
		{
			if (UPSMonsterWidget* MonsterWidget = Cast<UPSMonsterWidget>(Widget))
			{
				MonsterWidget->UpdateMonsterHP(EnemyStats.Health.GetPercent());
			}
		}
	}
}