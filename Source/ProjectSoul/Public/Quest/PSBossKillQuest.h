#pragma once

#include "CoreMinimal.h"
#include "Quest/PSQuestBase.h"
#include "PSBossKillQuest.generated.h"

UCLASS()
class PROJECTSOUL_API UPSBossKillQuest : public UPSQuestBase
{
	GENERATED_BODY()
	
public:
	UPSBossKillQuest();

	virtual bool ClearCondition() override;

	virtual FString QuestTextUpdate() override;

	virtual bool SetNextQuest() override;
protected:
	

};
