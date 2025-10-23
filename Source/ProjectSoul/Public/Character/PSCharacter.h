#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs/FPlayerStats.h"
#include "PSCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerStateMachine;
class USphereComponent;
class UAnimMontage;
class APSWeaponBase;
struct FInputActionValue;

UCLASS()
class PROJECTSOUL_API APSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RestoreAllStats();

	UFUNCTION(BlueprintPure, Category = "Targeting")
	bool GetIsTargeting() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnAttackEndNotify();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnEnableWeaponCollision();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnDisableWeaponCollision();

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetManaPercent() const;

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetStaminaPercent() const;

	float GetNormalWalkSpeed() const;

	float GetSprintWalkSpeed() const;

	float GetTargetingWalkSpeed() const;

	AActor* GetCurrentTarget() const;

	float GetMaxTargetDistance() const;

	UAnimMontage* GetDodgeMontage() const;

	UAnimMontage* GetAttackMontage() const;

	void SetCurrentTarget(AActor* NewTarget);

	void SetIsTargeting(bool Value);

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
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APSWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<APSWeaponBase> EquippedWeapon;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	bool bIsTargeting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	TObjectPtr<UAnimMontage> AttackMontage;
};
