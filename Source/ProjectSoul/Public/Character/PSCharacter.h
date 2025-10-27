#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs/FPlayerStats.h"
#include "PSCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChanged, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPChanged, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyTarget, AActor*, CurrentTarget);

class USpringArmComponent;
class UCameraComponent;
class UPlayerStateMachine;
class USphereComponent;
class UAnimMontage;
class APSWeaponBase;
class APSEnemy;
struct FInputActionValue;

UCLASS()
class PROJECTSOUL_API APSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCause
	) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RestoreAllStats();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnAttackEndNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnDodgeEndNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnHitEndNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnEnableWeaponCollisionNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnDisableWeaponCollisionNotify();

	UFUNCTION(BlueprintPure, Category = "Targeting")
	bool GetIsTargeting() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetManaPercent() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetStaminaPercent() const;

	UFUNCTION(BlueprintPure, Category = "Die")
	bool GetIsDead() const;

	float GetNormalWalkSpeed() const;

	float GetSprintWalkSpeed() const;

	float GetTargetingWalkSpeed() const;

	APSEnemy* GetCurrentTarget() const;

	float GetMaxTargetDistance() const;

	UAnimMontage* GetDodgeMontage() const;

	UAnimMontage* GetAttackMontage() const;

	UAnimMontage* GetHitMontage() const;

	void SetCurrentTarget(APSEnemy* NewTarget);

	void SetIsTargeting(bool Value);

	void SetIsSprinting(bool Value);

	void SetTargetingCamera();

	void ConsumeStaminaForAttack();

	void ConsumeStaminaForDodge();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump(const FInputActionValue& Value);

	UFUNCTION()
	void StopJump(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);

	UFUNCTION()
	void Lock(const FInputActionValue& Value);

	UFUNCTION()
	void Unlock(const FInputActionValue& Value);

	UFUNCTION()
	void Dodge(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

private:
	void FindTargetActor();
	
	void ConsumeStaminaForSprint();

	void StartStaminaRegen();

	void StopStaminaRegen();

	void RegenStamina();

	void OnDie();

public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHPChanged OnHPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnMPChanged OnMPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEnemyTarget OnEnemyTarget;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<USphereComponent> Scanner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UPlayerStateMachine> StateMachine;

	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	TObjectPtr<APSEnemy> CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APSWeaponBase> RightWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<APSWeaponBase> EquippedRightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APSWeaponBase> LeftWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<APSWeaponBase> EquippedLeftWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FPlayerStats PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TargetingWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float MaxTargetDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Stamina")
	float AttackStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Stamina")
	float DodgeStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Stamina")
	float SprintStaminaCostRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Stamina")
	float StaminaRegenDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats|Stamina")
	float StaminaRegenRate;

private:
	FTimerHandle SprintStaminaTimer;
	float SprintStaminaTimerInterval;
	bool bIsSprinting;

	FTimerHandle StaminaRegenDelayTimer;
	FTimerHandle StaminaRegenTickTimer;
	float StaminaRegenTickTimerInterval;

	bool bIsTargeting;

	bool bIsDead;

	FTimerHandle TestTimer;
};
