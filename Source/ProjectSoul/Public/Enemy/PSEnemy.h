#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs/FEnemyStats.h"
#include "PSEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHit, AActor*, Monster, float, Damage);

class UEnemyStateMachine;
class UStateMachineBase;
class UWidgetComponent;
class UBoxComponent;

UCLASS()
class PROJECTSOUL_API APSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	APSEnemy();

	virtual void SetMovementSpeed(float NewSpeed);

	virtual float GetWalkSpeed();

	virtual float GetChaseSpeed();

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void ShowHealthWidget(bool bShow);

	void SetIsDead(bool bIsdead);

	virtual UStateMachineBase* GetStateMachine();

	UAnimMontage* GetAttackMontage() const;

	UAnimMontage* GetDieMontage() const;

	UAnimMontage* GetHitMontage() const;

	FEnemyStats GetEnemyStats() const;

	UFUNCTION(BlueprintPure, Category = "Dead")
	virtual bool GetIsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Notify")
	virtual void DisableWeaponCollisionNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	virtual void EnableWeaponCollisionNotify();

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual UStateMachineBase* CreateStateMachine();

private:
	void UpdateHealthWidget();

	void ShowHitHealthWidget();

	void HiddenHitHealthWidget();


public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHit OnHit;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName AttachSocketNameL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName AttachSocketNameR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UStateMachineBase> StateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FEnemyStats EnemyStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float ChaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Collision")
	FVector WeaponR_BoxExtent = FVector(29.0f, 129.0f, 12.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Collision")
	FVector WeaponR_RelativeLocation = FVector(0.0f, 97.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Collision")
	FVector WeaponL_BoxExtent = FVector(29.0f, 129.0f, 12.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Collision")
	FVector WeaponL_RelativeLocation = FVector(0.0f, 97.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY()
	TSet<AActor*> DamagedActors;

private:
	bool bIsDead;

	bool bIsTargeted;

	bool bIsHit;

	FTimerHandle ShowMonsterHPTimer;
};
