#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerThrowState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerThrowState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

	virtual void Look(const FVector2D& Value) override;

	virtual void CanDodge() override;

	virtual void Dodge() override;

	virtual void Hit() override;

	virtual void Die() override;

	void ThrowEnd();

private:
	bool bCanDodge;
};
