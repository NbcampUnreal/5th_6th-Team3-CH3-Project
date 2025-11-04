#include "Quest/PSMonsterKillQuest.h"
#include "Quest/PSBossKillQuest.h"
#include "Gameplay/PSGameStateBase.h"

UPSMonsterKillQuest::UPSMonsterKillQuest()
{
	QuestName = "MonsterKill";
	NextQuest = nullptr;
	bIsActive = true;
	bIsClear = false;
}

bool UPSMonsterKillQuest::ClearCondition()
{
	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase)
	{
		if (GameStateBase->RemainingEnemies == 1)
		{
			bIsClear = true;

			return true;
		}
	}
	return false;
}

FString UPSMonsterKillQuest::QuestTextUpdate()
{
	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase) 
	{
		FString QuestText = FString::Printf(TEXT("Remaining Monsters : %d"), GameStateBase->RemainingEnemies-1);
		return QuestText;
	}
	return "";
}
//UPSQuestManagerSubsystem : QuestInit() call
bool UPSMonsterKillQuest::SetNextQuest()
{
	UPSQuestBase* KillQuest = NewObject<UPSBossKillQuest>(GetWorld()->GetGameInstance());
	if (KillQuest)
	{
		NextQuest = KillQuest;
		return true;
	}

	return false;
}
