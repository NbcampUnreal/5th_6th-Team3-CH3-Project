#pragma once

#include "CoreMinimal.h"
#include "State/PlayerStateBase.h"
#include "PlayerDieState.generated.h"

UCLASS()
class PROJECTSOUL_API UPlayerDieState : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnExit() override;
};
