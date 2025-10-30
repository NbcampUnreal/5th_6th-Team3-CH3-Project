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

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

private:
	void UpdateHealthWidget();

	void ShowHitHealthWidget();

	void HiddenHitHealthWidget();

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
