#include "Character/PSCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Gameplay/PSPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachine/PlayerStateMachine.h"
#include "State/PlayerStateBase.h"
#include "State/PlayerAttackState.h"
#include "Weapon/PSWeaponBase.h"

APSCharacter::APSCharacter()
	: NormalWalkSpeed(600.0f),
	SprintWalkSpeed(1200.0f),
	bIsTargeting(false)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (SpringArmComp)
	{
		SpringArmComp->SetupAttachment(RootComponent);
		SpringArmComp->bUsePawnControlRotation = true;
	}

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	if (CameraComp)
	{
		CameraComp->SetupAttachment(SpringArmComp);
	}

	Scanner = CreateDefaultSubobject<USphereComponent>(TEXT("Scanner"));
	if (Scanner)
	{
		Scanner->SetupAttachment(RootComponent);
		Scanner->SetSphereRadius(1000.0f);
	}

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void APSCharacter::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = NewObject<UPlayerStateMachine>(this);
	if (StateMachine)
	{
		StateMachine->Initialize(this);
	}

	if (WeaponClass)
	{
		EquippedWeapon = GetWorld()->SpawnActor<APSWeaponBase>(WeaponClass);
		UE_LOG(LogTemp, Warning, TEXT("Spawning weapon of class: %s"), *WeaponClass->GetName());
		if (EquippedWeapon)
		{
			EquippedWeapon->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				FName("RightWeapon")
			);
		}
	}
}

void APSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->OnUpdate(DeltaTime);
	}
}

void APSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			if (APSPlayerController* PlayerController = Cast<APSPlayerController>(GetController()))
			{
				if (PlayerController->MoveAction)
				{
					EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &APSCharacter::Move);
				}

				if (PlayerController->LookAction)
				{
					EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &APSCharacter::Look);
				}

				if (PlayerController->JumpAction)
				{
					EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &APSCharacter::StartJump);
					EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &APSCharacter::StopJump);
				}

				if (PlayerController->SprintAction)
				{
					EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &APSCharacter::StartSprint);
					EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &APSCharacter::StopSprint);
				}

				if (PlayerController->LockAction)
				{
					EnhancedInput->BindAction(PlayerController->LockAction, ETriggerEvent::Triggered, this, &APSCharacter::Lock);
				}

				if (PlayerController->UnlockAction)
				{
					EnhancedInput->BindAction(PlayerController->UnlockAction, ETriggerEvent::Triggered, this, &APSCharacter::Unlock);
				}

				if (PlayerController->DodgeAction)
				{
					EnhancedInput->BindAction(PlayerController->DodgeAction, ETriggerEvent::Triggered, this, &APSCharacter::Dodge);
				}

				if (PlayerController->AttackAction)
				{
					EnhancedInput->BindAction(PlayerController->AttackAction, ETriggerEvent::Triggered, this, &APSCharacter::Attack);
				}
			}
		}
	}
}

void APSCharacter::Move(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		FVector2D MoveInput = Value.Get<FVector2D>();
		StateMachine->GetCurrentState()->Move(MoveInput);
	}
}

void APSCharacter::Look(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		FVector2D LookInput = Value.Get<FVector2D>();
		StateMachine->GetCurrentState()->Look(LookInput);
	}
}

void APSCharacter::StartJump(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StartJump();
	}
}

void APSCharacter::StopJump(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StopJump();
	}
}

void APSCharacter::StartSprint(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StartSprint();
	}
}

void APSCharacter::StopSprint(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StopSprint();
	}
}

void APSCharacter::Lock(const FInputActionValue& Value)
{
	FindTargetActor();

	if (StateMachine && CurrentTarget)
	{
		StateMachine->GetCurrentState()->Lock();
	}
}

void APSCharacter::Unlock(const FInputActionValue& Value)
{
	CurrentTarget = nullptr;

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Unlock();
	}
}

void APSCharacter::Dodge(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Dodge();
	}
}

void APSCharacter::Attack(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Attack();
	}
}

float APSCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	PlayerStats.Health.AdjustValue(-DamageAmount);

	UE_LOG(LogTemp, Warning, TEXT("Player take damage %.0f from %s"), DamageAmount, *DamageCauser->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Player Remain Health: %.0f / %.0f"), PlayerStats.Health.GetCurrent(), PlayerStats.Health.GetMax());

	if (PlayerStats.Health.IsZero())
	{
		// Death
	}

	return ActualDamage;
}

void APSCharacter::FindTargetActor()
{
	if (!Scanner)
	{
		return;
	}

	TArray<AActor*> OverlappingActors;
	Scanner->GetOverlappingActors(OverlappingActors);

	AActor* ClosestActor = nullptr;
	float ClosestDist = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor || Actor == this)
		{
			continue;
		}

		if (Actor->ActorHasTag(TEXT("Enemy")))
		{
			float Dist = FVector::Distance(Actor->GetActorLocation(), GetActorLocation());
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				ClosestActor = Actor;
			}
		}
	}

	if (!ClosestActor)
	{
		CurrentTarget = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Not found enemy."));
		return;
	}

	CurrentTarget = ClosestActor;
	UE_LOG(LogTemp, Warning, TEXT("Found enemy: %s"), *CurrentTarget->GetName());
}

void APSCharacter::RestoreAllStats()
{
	PlayerStats.Health.RestoreFull();
	PlayerStats.Mana.RestoreFull();
	PlayerStats.Stamina.RestoreFull();
}

float APSCharacter::GetHealthPercent() const
{
	return PlayerStats.GetHealthPercent();
}

float APSCharacter::GetManaPercent() const
{
	return PlayerStats.GetManaPercent();
}

float APSCharacter::GetStaminaPercent() const
{
	return PlayerStats.GetStaminaPercent();
}

float APSCharacter::GetNormalWalkSpeed() const
{
	return NormalWalkSpeed;
}

float APSCharacter::GetSprintWalkSpeed() const
{
	return SprintWalkSpeed;
}

float APSCharacter::GetTargetingWalkSpeed() const
{
	return TargetingWalkSpeed;
}

AActor* APSCharacter::GetCurrentTarget() const
{
	return CurrentTarget;
}

float APSCharacter::GetMaxTargetDistance() const
{
	return MaxTargetDistance;
}

bool APSCharacter::GetIsTargeting() const
{
	return bIsTargeting;
}

UAnimMontage* APSCharacter::GetDodgeMontage() const
{
	return DodgeMontage;
}

UAnimMontage* APSCharacter::GetAttackMontage() const
{
	return AttackMontage;
}

void APSCharacter::SetCurrentTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
}

void APSCharacter::SetIsTargeting(bool Value)
{
	bIsTargeting = Value;
}

void APSCharacter::SetTargetingCamera()
{
	if (bIsTargeting)
	{
		SpringArmComp->TargetOffset = FVector(0.f, 0.f, 80.f);
		SpringArmComp->SocketOffset = FVector(0.f, 30.f, 0.f);
	}
	else
	{
		SpringArmComp->TargetOffset = FVector::ZeroVector;
		SpringArmComp->SocketOffset = FVector::ZeroVector;
	}
}

void APSCharacter::OnAttackEndNotify()
{
	if (StateMachine && StateMachine->GetAttackState())
	{
		StateMachine->GetAttackState()->AttackEnd();
	}
}

void APSCharacter::OnEnableWeaponCollision()
{
	EquippedWeapon->EnableWeaponCollision();
}

void APSCharacter::OnDisableWeaponCollision()
{
	EquippedWeapon->DisableWeaponCollision();
}