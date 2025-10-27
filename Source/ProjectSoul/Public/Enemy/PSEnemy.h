#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs/FEnemyStats.h"
#include "PSEnemy.generated.h"

class UEnemyStateMachine;
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

	virtual void DisableWeaponCollision();

	virtual void EnableWeaponCollision();

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void ShowHealthWidget(bool bShow);

	UEnemyStateMachine* GetStateMachine();

	UAnimMontage* GetAttackMontage() const;

	UAnimMontage* GetDieMontage() const;

	UAnimMontage* GetHitMontage() const;

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	void UpdateHealthWidget();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UEnemyStateMachine> StateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthWidget;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> HitMontage;
	UPROPERTY()
	TSet<AActor*> DamagedActors;
};
