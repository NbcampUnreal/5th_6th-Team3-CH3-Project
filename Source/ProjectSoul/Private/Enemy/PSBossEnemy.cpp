#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/PSBossProjectileBase.h"
#include "Components/BoxComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "StateMachine/BossEnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APSBossEnemy::APSBossEnemy()
{
	AIControllerClass = APSEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APSBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APSBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStateMachineBase* APSBossEnemy::CreateStateMachine()
{
	return NewObject<UBossEnemyStateMachine>(this);
}

UAnimMontage* APSBossEnemy::GetAttack1Montage() const
{
	return Attack_1_Montage;
}

UAnimMontage* APSBossEnemy::GetAttack2Montage() const
{
	return Attack_2_Montage;
}

UAnimMontage* APSBossEnemy::GetSkill1Montage() const
{
	return Skill_1_Montage;
}

UAnimMontage* APSBossEnemy::GetSkill2Montage() const
{
	return Skill_2_Montage;
}


void APSBossEnemy::Skill1Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy : Skill1"));

	AAIController* EnemyAIController = Cast<AAIController>(GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	AActor* Target = Cast<AActor>(BlackboardComp ? BlackboardComp->GetValueAsObject(TEXT("TargetActor")) : nullptr);

	if (!Target || !ProjectileClass)
		return;

	FVector TargetLocation = Target->GetActorLocation();
	FVector SpawnLocation = TargetLocation + FVector(0.f, 0.f, 1000.f); 
	FRotator SpawnRotation = FRotator(-90.f, 0.f, 0.f);

	FActorSpawnParameters Params;
	Params.Instigator = GetInstigator(); 

	APSBossProjectileBase* Projectile = GetWorld()->SpawnActor<APSBossProjectileBase>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		Params
	);

	if (Projectile)
	{
		Projectile->ProjectileMovement->bIsHomingProjectile = false;
		Projectile->ProjectileMovement->ProjectileGravityScale = 0.0f;
		Projectile->ProjectileMovement->InitialSpeed = 8000.f;
		Projectile->ProjectileMovement->MaxSpeed = 8000.f;
		Projectile->ProjectileMovement->Velocity = FVector(0.f, 0.f, -8000.f);
		Projectile->SetLifeSpan(3.0f);

		UE_LOG(LogTemp, Warning, TEXT("Skill1 Falling Projectile Spawned."));
	}
}


void APSBossEnemy::Skill2Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy : Skill2"));
	AAIController* EnemyAIController = Cast<AAIController>(this->GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
	if (!Target || !ProjectileClass) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150.f + FVector(0, 0, 80.f);
	FRotator SpawnRotation = (Target->GetActorLocation() - SpawnLocation).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();

	APSBossProjectileBase* Projectile = GetWorld()->SpawnActor<APSBossProjectileBase>(
		ProjectileClass, 
		SpawnLocation, 
		SpawnRotation, 
		Params);

	if (Projectile)
	{
		Projectile->SetHomingTarget(Target);
		Projectile->SetLifeSpan(5.0f);
		UE_LOG(LogTemp, Warning, TEXT("Skill2 Homing Projectile Spawned."));
	}
}