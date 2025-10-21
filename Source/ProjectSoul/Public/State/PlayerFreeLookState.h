#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerFreeLookState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerFreeLookState : public UPlayerStateBase
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

	virtual void Lock() override;
};
