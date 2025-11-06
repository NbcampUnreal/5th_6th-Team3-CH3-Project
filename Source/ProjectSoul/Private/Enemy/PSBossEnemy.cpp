#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/PSBossProjectileBase.h"
#include "Gameplay/PSAudioManagerSubsystem.h"
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

void APSBossEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		UE_LOG(LogTemp, Log, TEXT("Boss Die."));
		OnBossDefeated.Broadcast();
	}
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
	AAIController* EnemyAIController = Cast<AAIController>(GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	AActor* Target = Cast<AActor>(BlackboardComp ? BlackboardComp->GetValueAsObject(TEXT("TargetActor")) : nullptr);

	if (!Target || !ProjectileClass1)
		return;

	FVector TargetLocation = Target->GetActorLocation();
	FVector SpawnLocation = TargetLocation + FVector(0.f, 0.f, 270.f); 
	FRotator SpawnRotation = FRotator(-90.f, 0.f, 0.f);

	FActorSpawnParameters Params;
	Params.Instigator = GetInstigator(); 

	APSBossProjectileBase* Projectile = GetWorld()->SpawnActor<APSBossProjectileBase>(
		ProjectileClass1,
		SpawnLocation,
		SpawnRotation,
		Params
	);

	if (Projectile)
	{
		Projectile->ProjectileMovement->bIsHomingProjectile = false;
		Projectile->ProjectileMovement->ProjectileGravityScale = 0.0f;
		Projectile->ProjectileMovement->InitialSpeed = 1500.f;
		Projectile->ProjectileMovement->MaxSpeed = 1500.f;
		Projectile->ProjectileMovement->Velocity = FVector(0.f, 0.f, -1500.f);
		Projectile->SetLifeSpan(3.0f);
	}
}


void APSBossEnemy::Skill2Attack()
{
	AAIController* EnemyAIController = Cast<AAIController>(this->GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));

	if (!Target || !ProjectileClass2)
	{
		return;
	}

	FVector SocketLocation = GetMesh()->GetSocketLocation(TEXT("hand_l"));
	FRotator SocketRotation = GetMesh()->GetSocketRotation(TEXT("hand_l"));

	FVector SpawnLocation = SocketLocation + SocketRotation.Vector() * 100.f;
	FRotator SpawnRotation = (Target->GetActorLocation() - SpawnLocation).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();

	APSBossProjectileBase* Projectile = GetWorld()->SpawnActor<APSBossProjectileBase>(
		ProjectileClass2, 
		SpawnLocation, 
		SpawnRotation, 
		Params
	);

	if (Projectile)
	{
		Projectile->SetHomingTarget(Target);
		Projectile->SetLifeSpan(3.5f);
	}
}

void APSBossEnemy::OnPlayEnemyAttack2SoundNotify()
{
	if (Attack2Sound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(Attack2Sound, GetActorLocation(), 0.7f);
		}
	}
}

void APSBossEnemy::OnPlayEnemyAttack1SoundNotify()
{
	if (Attack1Sound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(Attack1Sound, GetActorLocation(), 0.7f);
		}
	}
}

void APSBossEnemy::OnPlayEnemySkill1SoundNotify()
{
	if (Skill1Sound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(Skill1Sound, GetActorLocation(), 0.7f);
		}
	}
}

void APSBossEnemy::OnPlayEnemySkill2SoundNotify()
{
	if (Skill2Sound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(Skill2Sound, GetActorLocation(), 0.7f);
		}
	}
}
