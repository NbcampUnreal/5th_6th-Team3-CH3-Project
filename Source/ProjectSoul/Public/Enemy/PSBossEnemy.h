#pragma once

#include "CoreMinimal.h"
#include "Enemy/PSEnemy.h"
#include "PSBossEnemy.generated.h"

class APSBossProjectileBase;
class FOnBossDefeated;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossDefeated);

UCLASS()
class PROJECTSOUL_API APSBossEnemy : public APSEnemy
{
	GENERATED_BODY() 

public:
	APSBossEnemy();

	void ShowHealthWidget(bool bShow);

	UAnimMontage* GetAttack1Montage() const;

	UAnimMontage* GetAttack2Montage() const;

	UAnimMontage* GetSkill1Montage() const;

	UAnimMontage* GetSkill2Montage() const;

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void Skill1Attack();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void Skill2Attack();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnPlayEnemyAttack1SoundNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnPlayEnemyAttack2SoundNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnPlayEnemySkill1SoundNotify();

	UFUNCTION(BlueprintCallable, Category = "Notify")
	void OnPlayEnemySkill2SoundNotify();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual UStateMachineBase* CreateStateMachine() override;

public:

	UPROPERTY(BlueprintAssignable) FOnBossDefeated OnBossDefeated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss|Montage")
	UAnimMontage* SpawnMontage;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<APSBossProjectileBase> ProjectileClass1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<APSBossProjectileBase> ProjectileClass2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Attack1Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Attack2Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Skill1Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Skill2Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Skill_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Skill_2_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Attack_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Attack_2_Montage;
};
