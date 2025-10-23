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

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void APSCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;

	StateMachine = NewObject<UPlayerStateMachine>(this);
	if (StateMachine)
	{
		StateMachine->Initialize(this);
	}
}

void APSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		FVector2D MoveInput = Value.Get<FVector2D>();
		StateMachine->GetCurrentState()->Move(MoveInput);
	}
}

void APSCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		FVector2D LookInput = Value.Get<FVector2D>();
		StateMachine->GetCurrentState()->Look(LookInput);
	}
}

void APSCharacter::StartJump(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;

	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StartJump();
	}
}

void APSCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StopJump();
	}
}

void APSCharacter::StartSprint(const FInputActionValue& Value)
{
	if (!Controller)
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
	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->StopSprint();
	}
}

void APSCharacter::Lock(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FindTargetActor();

	if (StateMachine && CurrentTarget)
	{
		StateMachine->GetCurrentState()->Lock();
	}
}

void APSCharacter::Unlock(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	CurrentTarget = nullptr;

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Unlock();
	}
}

void APSCharacter::Dodge(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Dodge input received."));

	if (!Controller)
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
	if (!Controller)
	{
		return;
	}

	if (StateMachine)
	{
		StateMachine->GetCurrentState()->Attack();
	}
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

void APSCharacter::OnAttackEndNotify()
{
	if (StateMachine && StateMachine->GetAttackState())
	{
		StateMachine->GetAttackState()->AttackEnd();
	}
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

void APSCharacter::SetCurrentTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
}

float APSCharacter::GetMaxTargetDistance() const
{
	return MaxTargetDistance;
}

void APSCharacter::SetIsTargeting(bool Value)
{
	bIsTargeting = Value;
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
