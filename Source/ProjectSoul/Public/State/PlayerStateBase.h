#pragma once

#include "CoreMinimal.h"
#include "State/StateBase.h"
#include "PlayerStateBase.generated.h"

class UPlayerStateMachine;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPlayerStateBase : public UStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

	virtual void Move(const FVector2D& Value);

	virtual void Look(const FVector2D& Value);

	virtual void StartSprint();

	virtual void StopSprint();

	virtual void StartJump();

	virtual void StopJump();

	virtual void Attack();

	virtual void Lock();

	virtual void Unlock();

	virtual void Dodge();

	virtual void Hit();

	virtual void Throw();

	virtual void Die();

protected:
	UPlayerStateMachine* GetPlayerStateMachine() const;

	APSCharacter* GetPlayerCharacter() const;
};
