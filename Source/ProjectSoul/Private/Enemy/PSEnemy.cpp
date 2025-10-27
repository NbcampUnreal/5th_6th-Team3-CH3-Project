#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Character/PSCharacter.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachine/EnemyStateMachine.h"
#include "State/EnemyStateBase.h"
#include "State/EnemyHitState.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "UI/PSMonsterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APSEnemy::APSEnemy()
	: Attack(20), 
	Score(50),
	WalkSpeed(200.0f),
	ChaseSpeed(400.0f)
{
	AIControllerClass = APSEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	if (HealthWidget)
	{
		HealthWidget->SetupAttachment(GetMesh());
		HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	if (BoxCollision)
	{
		BoxCollision->SetupAttachment(GetMesh());
		BoxCollision->SetBoxExtent(FVector(34.0f, 34.0f, 88.0f));
	}

	UCharacterMovementComponent* EnemyMovement = GetCharacterMovement();
	EnemyMovement->MaxWalkSpeed = WalkSpeed;
	EnemyMovement->bOrientRotationToMovement = true;

	EnemyStats.Health = FStat();
	EnemyStats.Stamina = FStat();
	WeaponCollisionL = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponL"));
	WeaponCollisionR = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponR"));
	if (WeaponCollisionL)
	{
		WeaponCollisionL->SetupAttachment(GetMesh());
	}
	if (WeaponCollisionR)
	{
		WeaponCollisionR->SetupAttachment(GetMesh());
	}
}

void APSEnemy::BeginPlay()
{
	Super::BeginPlay();
	StateMachine = NewObject<UEnemyStateMachine>(this);
	if (StateMachine)
	{
		StateMachine->Initialize(this);
	}
	if (WeaponCollisionR)
	{
		WeaponCollisionR->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_01"));
		WeaponCollisionR->RegisterComponent();
		WeaponCollisionR->OnComponentBeginOverlap.AddDynamic(this, &APSEnemy::OnWeaponOverlap);
	}
}

void APSEnemy::OnWeaponOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}

	/*if (DamagedActors.Contains(OtherActor))
	{
		return;
	}

	if (!OtherActor->ActorHasTag("Player"))
	{
		return;
	}*/

	DamagedActors.Add(OtherActor);
	UGameplayStatics::ApplyDamage(
		OtherActor,
		Attack,        
		nullptr,
		this,
		UDamageType::StaticClass()
	);
}

void APSEnemy::EnableWeaponCollision()
{
	UE_LOG(LogTemp, Log, TEXT("Enemy : weapon collision enabled"));
}

void APSEnemy::DisableWeaponCollision()
{
	UE_LOG(LogTemp, Log, TEXT("Enemy : weapon collision disabled"));
}

UEnemyStateMachine* APSEnemy::GetStateMachine()
{
	return StateMachine;
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
	AAIController* EnemyAIController = Cast<AAIController>(this->GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	BlackboardComp->SetValueAsBool(TEXT("bIsHit"), true);

	if (EnemyStats.Health.IsZero())
	{
		BlackboardComp->SetValueAsBool(TEXT("bIsDead"), true);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Death"));
	}

	return ActualDamage;
}

void APSEnemy::ShowHealthWidget(bool bShow)
{
	if (HealthWidget)
	{
		HealthWidget->SetVisibility(bShow);
	}
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

float APSEnemy::GetChaseSpeed()
{
	return ChaseSpeed;
}

float APSEnemy::GetWalkSpeed()
{
	return WalkSpeed;
}

UAnimMontage* APSEnemy::GetAttackMontage() const
{
	return AttackMontage;
}

UAnimMontage* APSEnemy::GetDieMontage() const
{
	return DieMontage;
}

UAnimMontage* APSEnemy::GetHitMontage() const
{
	return HitMontage;
}
