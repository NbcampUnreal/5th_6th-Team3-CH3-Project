#include "Quest/PSQuestBase.h"

UPSQuestBase::UPSQuestBase()
{
}

FName UPSQuestBase::GetQuestName()
{
	return QuestName;
}

bool UPSQuestBase::ClearCondition()
{
	return false;
}

FString UPSQuestBase::QuestTextUpdate()
{
	return "";
}

bool UPSQuestBase::SetNextQuest()
{
	return false;
}

UPSQuestBase* UPSQuestBase::GetNextQuest()
{
	return NextQuest;
}
