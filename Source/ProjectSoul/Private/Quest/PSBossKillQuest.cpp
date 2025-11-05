#include "Quest/PSBossKillQuest.h"
#include "Gameplay/PSGameStateBase.h"

UPSBossKillQuest::UPSBossKillQuest()
{
	QuestName = "BossKill";
	NextQuest = nullptr;
	bIsActive = true;
	bIsClear = false;
}

bool UPSBossKillQuest::ClearCondition()
{
	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase)
	{
		if (false)
		{
			bIsClear = true;

			return true;
		}
	}
	return false;
}

FString UPSBossKillQuest::QuestTextUpdate()
{
	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	FString QuestText = FString::Printf(TEXT("Boss Kill"));
	return QuestText;
}
//UPSQuestManagerSubsystem : QuestInit() call
bool UPSBossKillQuest::SetNextQuest()
{

	return false;
}

