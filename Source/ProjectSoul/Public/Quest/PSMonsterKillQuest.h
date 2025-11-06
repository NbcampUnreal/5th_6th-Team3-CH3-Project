#pragma once

#include "CoreMinimal.h"
#include "Quest/PSQuestBase.h"
#include "PSMonsterKillQuest.generated.h"

UCLASS()
class PROJECTSOUL_API UPSMonsterKillQuest : public UPSQuestBase
{
	GENERATED_BODY()
	
public:
	UPSMonsterKillQuest();

	virtual bool ClearCondition() override;

	virtual FString QuestTextUpdate() override;

	virtual bool SetNextQuest() override;
};
