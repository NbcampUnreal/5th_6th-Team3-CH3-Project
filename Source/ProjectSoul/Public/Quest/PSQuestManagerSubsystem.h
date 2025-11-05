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
	
	UFUNCTION()
	void QuestInit();

	void UpdateQuest(TMap<FName, UPSQuestTextWidget*>* QuestWidget);

	

private:
	void CreateQuest();

public:
	UPROPERTY()
	TArray<UPSQuestBase*> ActiveQuests;
	UPROPERTY()
	TObjectPtr<UPSQuestBase> CheckQuest;

	TArray<UPSQuestBase*> QuestsToRemove;
	TArray<UPSQuestBase*> QuestsToAdd;

	bool bIsQuestInit;
};
