#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "BossEnemyAttackState.generated.h"

UCLASS()
class PROJECTSOUL_API UBossEnemyAttackState : public UEnemyStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnter() override;

	virtual void OnExit() override;

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	FOnMontageEnded EndDelegate;
};
