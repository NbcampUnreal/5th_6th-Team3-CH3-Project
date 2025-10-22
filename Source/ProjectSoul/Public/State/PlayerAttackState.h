#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerAttackState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerAttackState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

private:
	void AttackEnd();

private:
	FTimerHandle TestTimer;
};
