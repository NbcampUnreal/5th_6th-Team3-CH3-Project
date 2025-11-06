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

	virtual bool ClearCondition();

	virtual FString QuestTextUpdate();

	virtual bool SetNextQuest();

	FName GetQuestName();

	UPSQuestBase* GetNextQuest();

protected:
	FName QuestName;

	UPROPERTY(Transient)
	TObjectPtr<UPSQuestBase> NextQuest;

	bool bIsActive;

	bool bIsClear;
};
