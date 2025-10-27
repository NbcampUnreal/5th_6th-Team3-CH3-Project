#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerHitState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerHitState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

	virtual void Die() override;

	UFUNCTION(BlueprintCallable)
	void HitEnd();
};
