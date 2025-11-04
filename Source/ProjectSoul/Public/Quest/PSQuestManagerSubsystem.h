#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PSQuestManagerSubsystem.generated.h"

class UPSQuestBase;
class UPSQuestTextWidget;

UCLASS()
class PROJECTSOUL_API UPSQuestManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPSQuestManagerSubsystem();
	
	void QuestInit();

	void UpdateQuest(TMap<FName, UPSQuestTextWidget*> QuestWidget);

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UPROPERTY()
	TArray<UPSQuestBase*> ActiveQuests;
	UPROPERTY()
	TObjectPtr<UPSQuestBase> CheckQuest;

	bool bIsQuestInit;
};
