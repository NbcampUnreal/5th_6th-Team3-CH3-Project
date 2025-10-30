#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Gameplay/PSGameModeBase.h"
#include "Character/PSCharacter.h"
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

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	if (HealthWidgetComponent)
	{
		HealthWidgetComponent->SetupAttachment(GetMesh());
		HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
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
	StateMachine = CreateStateMachine();
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
		WeaponCollisionR->SetRelativeLocation(WeaponR_RelativeLocation);
		WeaponCollisionR->SetBoxExtent(WeaponR_BoxExtent);
		WeaponCollisionR->RegisterComponent();
		WeaponCollisionR->OnComponentBeginOverlap.AddDynamic(this, &APSEnemy::OnWeaponOverlap);
	}
	if (WeaponCollisionL)
	{
		WeaponCollisionL->SetRelativeLocation(WeaponL_RelativeLocation);
		WeaponCollisionL->SetBoxExtent(WeaponL_BoxExtent);
		WeaponCollisionL->RegisterComponent();
		WeaponCollisionL->OnComponentBeginOverlap.AddDynamic(this, &APSEnemy::OnWeaponOverlap);
	}
	DisableWeaponCollisionNotify();
}

void APSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsTargeted || bIsHit)
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector WidgetCompLocation = HealthWidgetComponent->GetComponentLocation();

		FVector Direction = CameraLocation - WidgetCompLocation;
		Direction.Normalize();

		FRotator LookRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		HealthWidgetComponent->SetWorldRotation(LookRotation);
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

	if (OtherComp)
	{
		if (OtherComp->GetName() != TEXT("CollisionCylinder"))
		{
			return;
		}
	}

	if (DamagedActors.Contains(OtherActor))
	{
		return;
	}

	if (!OtherActor->ActorHasTag("Player"))
	{
		return;
	}
	AAIController* EnemyAIController = Cast<AAIController>(this->GetController());
	UBlackboardComponent* BlackboardComp = EnemyAIController ? EnemyAIController->GetBlackboardComponent() : nullptr;

	if (EnemyAIController == nullptr || BlackboardComp == nullptr)
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

UStateMachineBase* APSEnemy::CreateStateMachine()
{
	return NewObject<UEnemyStateMachine>(this);
}

UStateMachineBase* APSEnemy::GetStateMachine()
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

	if (EnemyStats.Health.IsZero())
	{
		BlackboardComp->SetValueAsBool(TEXT("bIsAttacking"), false);
		BlackboardComp->SetValueAsBool(TEXT("bInAttackRange"), false);
		BlackboardComp->SetValueAsBool(TEXT("bIsDead"), true);
		UE_LOG(LogTemp, Warning, TEXT("Enemy Death"));

		if (APSGameModeBase* GM = Cast<APSGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			GM->OnEnemyKilled(Score);
		}
	}
	else
	{
		BlackboardComp->SetValueAsBool(TEXT("bIsHit"), true);
		BlackboardComp->SetValueAsVector(TEXT("TargetLastKnownLocation"), DamageCauser->GetActorLocation());
		BlackboardComp->SetValueAsBool(TEXT("bIsInvestigating"), true);
		//PSPlayerHUDWidget class Function Call
		OnHit.Broadcast(this, ActualDamage);
	}
	return ActualDamage;
}

//Lock On Call
void APSEnemy::ShowHealthWidget(bool bShow)
{
	if (HealthWidgetComponent)
	{
		bIsTargeted = bShow;
		HealthWidgetComponent->SetVisibility(bShow);
	}
}

void APSEnemy::ShowHitHealthWidget()
{
	bIsHit = true;
	HealthWidgetComponent->SetVisibility(true);
	
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
		HealthWidgetComponent->SetVisibility(false);
		GetWorld()->GetTimerManager().ClearTimer(ShowMonsterHPTimer);
	}
	bIsHit = false;
}

void APSEnemy::UpdateHealthWidget()
{
	if (HealthWidgetComponent)
	{
		if (UUserWidget* Widget = HealthWidgetComponent->GetUserWidgetObject())
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

FEnemyStats APSEnemy::GetEnemyStats() const
{
	return EnemyStats;
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