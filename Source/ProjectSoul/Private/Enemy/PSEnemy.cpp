#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Gameplay/PSGameModeBase.h"
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

#include "UI/PSUIManagerSubsystem.h"
#include "UI/PSPlayerHUDWidget.h"

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
	if (!AttachSocketNameL.IsNone())
	{
		WeaponCollisionL->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			AttachSocketNameL
		);
	}
	if (!AttachSocketNameR.IsNone())
	{
		WeaponCollisionR->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			AttachSocketNameR
		);
	}
	if (WeaponCollisionR)
	{
		WeaponCollisionR->RegisterComponent();
		WeaponCollisionR->OnComponentBeginOverlap.AddDynamic(this, &APSEnemy::OnWeaponOverlap);
	}
	if (WeaponCollisionL)
	{

		WeaponCollisionL->RegisterComponent();
		WeaponCollisionL->OnComponentBeginOverlap.AddDynamic(this, &APSEnemy::OnWeaponOverlap);
	}
}

void APSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTargeted || bIsHit)
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector WidgetCompLocation = HealthWidget->GetComponentLocation();

		FVector Direction = CameraLocation - WidgetCompLocation;
		Direction.Normalize();

		FRotator LookRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		HealthWidget->SetWorldRotation(LookRotation);
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

	if (DamagedActors.Contains(OtherActor))
	{
		return;
	}

	if (!OtherActor->ActorHasTag("Player"))
	{
		return;
	}

	DamagedActors.Add(OtherActor);
	UGameplayStatics::ApplyDamage(
		OtherActor,
		Attack,        
		nullptr,
		this,
		UDamageType::StaticClass()
	);
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
	ShowHitHealthWidget();
	UE_LOG(LogTemp, Warning, TEXT("Enemy take damage %.0f from %s"), DamageAmount, *DamageCauser->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Enemy Remain Health: %.0f / %.0f"), EnemyStats.Health.GetCurrent(), EnemyStats.Health.GetMax());
	AAIController* EnemyAIController = Cast<AAIController>(this->GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;
	BlackboardComp->SetValueAsBool(TEXT("bIsHit"), true);

	if (EnemyStats.Health.IsZero())
	{
		BlackboardComp->SetValueAsBool(TEXT("bIsDead"), true);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Death"));

		if (APSGameModeBase* GM = Cast<APSGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			GM->OnEnemyKilled(Score);
		}
	}
	OnHit.Broadcast(this, ActualDamage);

	return ActualDamage;
}

void APSEnemy::ShowHealthWidget(bool bShow)
{
	if (HealthWidget)
	{
		bIsTargeted = bShow;
		HealthWidget->SetVisibility(bShow);
	}
}

void APSEnemy::ShowHitHealthWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("HP Bar On"));
	bIsHit = true;
	HealthWidget->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(
		ShowMonsterHPTimer,
		this,
		&APSEnemy::HiddenHitHealthWidget,
		3.0f
	);
}

void APSEnemy::HiddenHitHealthWidget()
{
	if (!bIsTargeted)
	{
		UE_LOG(LogTemp, Warning, TEXT("HP Bar Off"));
		HealthWidget->SetVisibility(false);
		GetWorld()->GetTimerManager().ClearTimer(ShowMonsterHPTimer);
	}
	bIsHit = false;
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

void APSEnemy::EnableWeaponCollisionNotify()
{
	WeaponCollisionR->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponCollisionL->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APSEnemy::DisableWeaponCollisionNotify()
{
	WeaponCollisionR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamagedActors.Empty(); // Initialize the list
}

void APSEnemy::SetIsDead(bool bIsdead)
{
	bIsDead = bIsdead;
}

bool APSEnemy::GetIsDead() const
{
	return bIsDead;
}