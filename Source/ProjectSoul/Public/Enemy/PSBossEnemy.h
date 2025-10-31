#pragma once

#include "CoreMinimal.h"
#include "Enemy/PSEnemy.h"
#include "PSBossEnemy.generated.h"

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

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	virtual UStateMachineBase* CreateStateMachine() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Skill_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Skill_2_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Attack_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TObjectPtr<UAnimMontage> Attack_2_Montage;
};
