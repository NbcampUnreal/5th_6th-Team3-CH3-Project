#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerDodgeState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerDodgeState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;

	virtual void Look(const FVector2D& Value) override;

	UFUNCTION(BlueprintCallable)
	void DodgeEnd();
};
