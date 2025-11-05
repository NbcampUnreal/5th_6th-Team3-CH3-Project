#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSQuestBase.generated.h"

UCLASS()
class PROJECTSOUL_API UPSQuestBase : public UObject
{
	GENERATED_BODY()

public:
	UPSQuestBase();

	FName GetQuestName();

	virtual bool ClearCondition();

	virtual FString QuestTextUpdate();

	virtual bool SetNextQuest();

	UPSQuestBase* GetNextQuest();

protected:
	

protected:
	FName QuestName;

	UPROPERTY(Transient)
	TObjectPtr<UPSQuestBase> NextQuest;

	bool bIsActive;

	bool bIsClear;
};
