#include "Character/PSCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/PSPlayerController.h"
#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSAudioManagerSubsystem.h"
#include "StateMachine/PlayerStateMachine.h"
#include "State/PlayerTargetingState.h"
#include "State/PlayerStateBase.h"
#include "State/PlayerAttackState.h"
#include "State/PlayerDodgeState.h"
#include "State/PlayerHitState.h"
#include "State/PlayerThrowState.h"
#include "State/PlayerHealState.h"
#include "Weapon/PSWeaponBase.h"
#include "Weapon/PSFireBomb.h"
#include "Enemy/PSEnemy.h"

APSCharacter::APSCharacter()
	: NormalWalkSpeed(600.0f),
	SprintWalkSpeed(1200.0f),
	HealingPotionCount(3),
	bIsTargeting(false),
	bIsSprinting(false),
	bIsDead(false),
	bIsInvulnerable(false),
	SprintStaminaTimerInterval(0.1f),
	StaminaRegenTickTimerInterval(0.1f),
	LastMoveInput(FVector2D::ZeroVector)
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

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void APSCharacter::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = NewObject<UPlayerStateMachine>(this);
	if (StateMachine)
	{
		StateMachine->Initialize(this);
	}

	if (RightWeaponClass)
	{
		EquippedRightWeapon = GetWorld()->SpawnActor<APSWeaponBase>(RightWeaponClass);
		if (EquippedRightWeapon)
		{
			EquippedRightWeapon->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				FName("RightWeapon")
			);
		}
	}

	if (LeftWeaponClass)
	{
		EquippedLeftWeapon = GetWorld()->SpawnActor<APSWeaponBase>(LeftWeaponClass);
		if (EquippedLeftWeapon)
		{
			EquippedLeftWeapon->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				FName("LeftWeapon")
			);
		}
	}

	OnHPChanged.Broadcast(PlayerStats.Health.GetCurrent(), PlayerStats.Health.GetMax());
	OnMPChanged.Broadcast(PlayerStats.Mana.GetCurrent(), PlayerStats.Mana.GetMax());
	OnStaminaChanged.Broadcast(PlayerStats.Stamina.GetCurrent(), PlayerStats.Stamina.GetMax());
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
					EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &APSCharacter::Move);
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

				if (PlayerController->ThrowAction)
				{
					EnhancedInput->BindAction(PlayerController->ThrowAction, ETriggerEvent::Triggered, this, &APSCharacter::Throw);
				}

				if (PlayerController->HealAction)
				{
					EnhancedInput->BindAction(PlayerController->HealAction, ETriggerEvent::Triggered, this, &APSCharacter::Heal);
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
		LastMoveInput = MoveInput.IsNearlyZero() ? FVector2D::ZeroVector : MoveInput;
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
	if (PlayerStats.Stamina.IsZero())
	{
		return;
	}

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
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Lock();
	}
}

void APSCharacter::Unlock(const FInputActionValue& Value)
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Unlock();
	}
}

void APSCharacter::Dodge(const FInputActionValue& Value)
{
	if (PlayerStats.Stamina.IsZero() || IsFalling())
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Dodge();
	}
}

void APSCharacter::Attack(const FInputActionValue& Value)
{
	if (PlayerStats.Stamina.IsZero() || IsFalling())
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Attack();
	}
}

void APSCharacter::Throw(const FInputActionValue& Value)
{
	if (PlayerStats.Mana.IsZero() || IsFalling())
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Throw();
	}
}

void APSCharacter::Heal(const FInputActionValue& Value)
{
	if (!RemainHealingPotion())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: No Potion Remaining."));
		return;
	}

	if (IsFalling())
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Heal();
	}
}

float APSCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: Already dead - No damage taken."));
		return 0.0f;
	}

	if (bIsInvulnerable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: Invulnerable - No damage taken."));
		return 0.0f;
	}

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	PlayerStats.Health.AdjustValue(-DamageAmount);
	OnHPChanged.Broadcast(PlayerStats.Health.GetCurrent(), PlayerStats.Health.GetMax());

	UE_LOG(LogTemp, Warning, TEXT("Player: take damage %.0f from %s"), DamageAmount, *DamageCauser->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Player: Remain Health: %.0f / %.0f"), PlayerStats.Health.GetCurrent(), PlayerStats.Health.GetMax());

	if (PlayerStats.Health.IsZero())
	{
		OnDie();
	}
	else
	{
		if (StateMachine)
		{
			StateMachine->GetCurrentState()->Hit();
		}
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

	APSEnemy* ClosestEnemy = nullptr;
	float ClosestDist = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor || Actor == this)
		{
			continue;
		}

		if (APSEnemy* Enemy = Cast<APSEnemy>(Actor))
		{
			if (Enemy->GetIsDead())
			{
				continue;
			}

			float Dist = FVector::Distance(Enemy->GetActorLocation(), GetActorLocation());
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				ClosestEnemy = Enemy;
			}
		}
	}

	if (!ClosestEnemy)
	{
		CurrentTarget = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Player: Not found enemy."));
		return;
	}

	SetCurrentTarget(ClosestEnemy);
	UE_LOG(LogTemp, Warning, TEXT("Player: Found enemy: %s"), *CurrentTarget->GetName());
}

void APSCharacter::RestoreAllStats()
{
	PlayerStats.Health.RestoreFull();
	PlayerStats.Mana.RestoreFull();
	PlayerStats.Stamina.RestoreFull();
}

void APSCharacter::ConsumeStaminaForAttack()
{
	StopStaminaRegen();

	PlayerStats.Stamina.AdjustValue(-AttackStaminaCost);
	OnStaminaChanged.Broadcast(PlayerStats.Stamina.GetCurrent(), PlayerStats.Stamina.GetMax());
}

void APSCharacter::ConsumeStaminaForDodge()
{
	StopStaminaRegen();

	PlayerStats.Stamina.AdjustValue(-DodgeStaminaCost);
	OnStaminaChanged.Broadcast(PlayerStats.Stamina.GetCurrent(), PlayerStats.Stamina.GetMax());
}

void APSCharacter::ConsumeManaForThrow()
{
	PlayerStats.Mana.AdjustValue(-ThrowManaCost);
	OnMPChanged.Broadcast(PlayerStats.Mana.GetCurrent(), PlayerStats.Mana.GetMax());
}

void APSCharacter::AddHealth(float Amount)
{
	if (Amount <= 0.0f)
	{
		return;
	}

	PlayerStats.Health.AdjustValue(+Amount);
	OnHPChanged.Broadcast(PlayerStats.Health.GetCurrent(), PlayerStats.Health.GetMax());
}

void APSCharacter::OnTargetDie(AActor* DeadTarget)
{
	if (CurrentTarget == DeadTarget)
	{
		GetWorldTimerManager().SetTimer(
			EnemyDeadTimer,
			this,
			&APSCharacter::TargetUnlock,
			1.0f,
			false
		);
	}
}

void APSCharacter::TargetUnlock()
{
	if (StateMachine)
	{
		StateMachine->GetTargetingState()->Unlock();
	}
}

void APSCharacter::ConsumeStaminaForSprint()
{
	StopStaminaRegen();

	PlayerStats.Stamina.AdjustValue(-SprintStaminaCostRate * SprintStaminaTimerInterval);
	OnStaminaChanged.Broadcast(PlayerStats.Stamina.GetCurrent(), PlayerStats.Stamina.GetMax());

	if (PlayerStats.Stamina.IsZero())
	{
		if (StateMachine)
		{
			StateMachine->GetCurrentState()->StopSprint();
		}

		SetIsSprinting(false);
	}
}

void APSCharacter::StopStaminaRegen()
{
	GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTickTimer);
	GetWorld()->GetTimerManager().ClearTimer(StaminaRegenDelayTimer);

	GetWorld()->GetTimerManager().SetTimer(
		StaminaRegenDelayTimer,
		this,
		&APSCharacter::StartStaminaRegen,
		StaminaRegenDelay,
		false
	);
}

void APSCharacter::StartStaminaRegen()
{
	if (PlayerStats.Stamina.IsFull())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		StaminaRegenTickTimer,
		this,
		&APSCharacter::RegenStamina,
		StaminaRegenTickTimerInterval,
		true
	);
}

void APSCharacter::RegenStamina()
{
	PlayerStats.Stamina.AdjustValue(StaminaRegenRate * StaminaRegenTickTimerInterval);
	OnStaminaChanged.Broadcast(PlayerStats.Stamina.GetCurrent(), PlayerStats.Stamina.GetMax());

	if (PlayerStats.Stamina.IsFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTickTimer);
	}
}

void APSCharacter::OnDie()
{
	bIsDead = true;
	UE_LOG(LogTemp, Warning, TEXT("Player: Dead"));

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Die();
	}

	if (APSGameModeBase* GM = Cast<APSGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GM->EndGame(false);
	}
}

bool APSCharacter::IsFalling() const
{
	return GetCharacterMovement()->IsFalling();
}

bool APSCharacter::RemainHealingPotion() const
{
	return HealingPotionCount > 0 ? true : false;
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

APSEnemy* APSCharacter::GetCurrentTarget() const
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

bool APSCharacter::GetIsDead() const
{
	return bIsDead;
}

UAnimMontage* APSCharacter::GetDodgeMontage() const
{
	return DodgeMontage;
}

UAnimMontage* APSCharacter::GetAttackMontage(int32 Index) const
{
	return AttackMontage[Index];
}

UAnimMontage* APSCharacter::GetHitMontage() const
{
	return HitMontage;
}

UAnimMontage* APSCharacter::GetThrowMontage() const
{
	return ThrowMontage;
}

UAnimMontage* APSCharacter::GetHealMontage() const
{
	return HealMontage;
}

FVector2D APSCharacter::GetLastMoveInput() const
{
	return LastMoveInput;
}

int32 APSCharacter::GetHealingPotionCount() const
{
	return HealingPotionCount;
}

void APSCharacter::SetCurrentTarget(APSEnemy* NewTarget)
{
	if (CurrentTarget)
	{
		CurrentTarget->OnEnemyDie.RemoveDynamic(this, &APSCharacter::OnTargetDie);
	}

	CurrentTarget = NewTarget;
	if (CurrentTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bind OnEnemyDie Event"));
		CurrentTarget->OnEnemyDie.AddDynamic(this, &APSCharacter::OnTargetDie);
	}

	OnEnemyTarget.Broadcast(CurrentTarget);
}

void APSCharacter::SetIsTargeting(bool Value)
{
	bIsTargeting = Value;
}

void APSCharacter::SetIsSprinting(bool Value)
{
	if (Value && !bIsSprinting)
	{
		GetWorld()->GetTimerManager().ClearTimer(SprintStaminaTimer);

		GetWorld()->GetTimerManager().SetTimer(
			SprintStaminaTimer,
			this,
			&APSCharacter::ConsumeStaminaForSprint,
			SprintStaminaTimerInterval,
			true
		);
	}
	else if (!Value && bIsSprinting)
	{
		GetWorld()->GetTimerManager().ClearTimer(SprintStaminaTimer);
	}

	bIsSprinting = Value;
}

void APSCharacter::SetIsInvulnerable(bool Value)
{
	bIsInvulnerable = Value;
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

void APSCharacter::OnEnableWeaponCollisionNotify()
{
	EquippedRightWeapon->EnableWeaponCollision();
}

void APSCharacter::OnDisableWeaponCollisionNotify()
{
	EquippedRightWeapon->DisableWeaponCollision();
}

void APSCharacter::OnNextComboWindowNotify()
{
	if (StateMachine && StateMachine->GetAttackState())
	{
		StateMachine->GetAttackState()->NextComboWindow();
	}
}

void APSCharacter::OnStartNextComboNotify()
{
	if (StateMachine && StateMachine->GetAttackState())
	{
		StateMachine->GetAttackState()->StartNextCombo();
	}
}

void APSCharacter::OnDodgeEndNotify()
{
	if (StateMachine && StateMachine->GetDodgeState())
	{
		StateMachine->GetDodgeState()->DodgeEnd();
	}
}

void APSCharacter::OnInvulnerableStartNotify()
{
	if (StateMachine && StateMachine->GetDodgeState())
	{
		StateMachine->GetDodgeState()->InvulnerableStart();
	}
}

void APSCharacter::OnInvulnerableEndNotify()
{
	if (StateMachine && StateMachine->GetDodgeState())
	{
		StateMachine->GetDodgeState()->InvulnerableEnd();
	}
}

void APSCharacter::OnCanDodgeNotify()
{
	if (StateMachine)
	{
		StateMachine->GetCurrentState()->CanDodge();
	}
}

void APSCharacter::OnHitEndNotify()
{
	if (StateMachine && StateMachine->GetHitState())
	{
		StateMachine->GetHitState()->HitEnd();
	}
}

void APSCharacter::OnThrowObjectNotify()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: Throw Object Notify"));

	if (ThrowObjectClass)
	{
		FVector HandLocation = GetMesh()->GetSocketLocation(FName("RightHand"));
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Pitch = 0.0f;

		FVector ForwardVector = ActorRotation.Vector();
		FVector SpawnLocation = HandLocation + ForwardVector * 50.0f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AActor* ThrownObject = GetWorld()->SpawnActor<AActor>(
			ThrowObjectClass,
			SpawnLocation,
			ActorRotation,
			SpawnParams
		);

		if (ThrownObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player: Spawned throw object: %s"), *ThrownObject->GetName());

			if (APSFireBomb* Bomb = Cast<APSFireBomb>(ThrownObject))
			{
				FVector LaunchDir = ActorRotation.Vector();
				LaunchDir.Z += 0.5f;
				LaunchDir.Normalize();

				Bomb->Init(LaunchDir);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player: Failed to spawn throw object"));
		}
	}
}

void APSCharacter::OnThrowEndNotify()
{
	if (StateMachine && StateMachine->GetThrowState())
	{
		StateMachine->GetThrowState()->ThrowEnd();
	}
}

void APSCharacter::OnHealingNotify()
{
	UE_LOG(LogTemp, Warning, TEXT("Player: %.1f Healing"), 50.f);

	HealingPotionCount--;
	OnPotionCountChanged.Broadcast(HealingPotionCount);
	AddHealth(50.f);
}

void APSCharacter::OnHealEndNotify()
{
	if (StateMachine && StateMachine->GetThrowState())
	{
		StateMachine->GetThrowState()->ThrowEnd();
	}
}

void APSCharacter::OnPlayFootstepSoundNotify()
{
	if (FootstepSound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(FootstepSound, GetActorLocation(), 0.3f);
		}
	}
}

void APSCharacter::OnPlayAttackSoundNotify()
{
	if (EquippedRightWeapon->GetAttackSound())
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(EquippedRightWeapon->GetAttackSound(), GetActorLocation(), 0.7f);
		}
	}
}

void APSCharacter::OnPlayJumpSoundNotify()
{
	if (JumpSound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(JumpSound, GetActorLocation(), 0.7f);
		}
	}
}

void APSCharacter::OnPlayLandSoundNotify()
{
	if (LandSound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(LandSound, GetActorLocation(), 0.7f);
		}
	}
}

void APSCharacter::OnPlayDodgeSoundNotify()
{
	if (DodgeSound)
	{
		if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
		{
			Audio->PlaySFX(DodgeSound, GetActorLocation(), 0.7f);
		}
	}
}
