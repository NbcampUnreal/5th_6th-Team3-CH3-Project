#pragma once

#include "CoreMinimal.h"
#include "State/EnemyStateBase.h"
#include "EnemyReturnState.generated.h"

struct FAIRequestID;
struct FPathFollowingResult;
UCLASS()
class PROJECTSOUL_API UEnemyReturnState : public UEnemyStateBase
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() override;

	virtual void OnExit() override;

	void HandleMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
