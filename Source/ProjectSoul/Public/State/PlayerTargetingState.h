#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerTargetingState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerTargetingState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

	virtual void Move(const FVector2D& Value) override;

	virtual void Look(const FVector2D& Value) override;

	virtual void StartSprint() override;

	virtual void StopSprint() override;

	virtual void StartJump() override;

	virtual void StopJump() override;

	virtual void Attack() override;

	virtual void Unlock() override;

private:
	void CalculateTargetRotation(float DeltaTime);

	float CalculateTargetDistance();

	bool IsTargetTooFar();
};
