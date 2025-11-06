#include "Quest/PSQuestManagerSubsystem.h"
#include "Quest/PSQuestBase.h"
#include "Quest/PSMonsterKillQuest.h"
#include "Quest/PSBossKillQuest.h"
#include "UI/PSQuestTextWidget.h"

UPSQuestManagerSubsystem::UPSQuestManagerSubsystem()
{
    CheckQuest = nullptr;
    bIsQuestInit = false;
}

void UPSQuestManagerSubsystem::CreateQuest()
{
    UPSQuestBase* MonsterKillQuest = NewObject<UPSMonsterKillQuest>(GetGameInstance());

    if (MonsterKillQuest)
    {
        ActiveQuests.Add(MonsterKillQuest);
    }
}

void UPSQuestManagerSubsystem::QuestInit()
{
    ActiveQuests.Empty();

    CreateQuest();

    for (UPSQuestBase* Quest : ActiveQuests)
    {
        CheckQuest = Quest;
        while (true)
        {
            if (CheckQuest->SetNextQuest())
            {
                CheckQuest = CheckQuest->GetNextQuest();
            }
            else
            {
                break;
            }
        }
    }
}

void UPSQuestManagerSubsystem::UpdateQuest(TMap<FName, UPSQuestTextWidget*>* QuestWidget)
{
    for (int i = 0; i < ActiveQuests.Num(); i++)
    {
        CheckQuest = ActiveQuests[i];
        if (!IsValid(CheckQuest))
        {
            QuestsToRemove.Add(CheckQuest);
            continue;
        }

        if (CheckQuest->ClearCondition())
        {
            if (UPSQuestBase* NextQuest = CheckQuest->GetNextQuest())
            {
                QuestsToAdd.Add(NextQuest);
            }

            if (QuestWidget->Contains(CheckQuest->GetQuestName()))
            {
                UPSQuestTextWidget* Widget = (*QuestWidget)[CheckQuest->GetQuestName()];
                if (IsValid(Widget))
                {
                    QuestWidget->Remove(CheckQuest->GetQuestName());
                    Widget->RemoveFromParent();
                }
            }

            QuestsToRemove.Add(CheckQuest);
        }     
    }

    for (UPSQuestBase* Quest : QuestsToRemove)
    {
        ActiveQuests.Remove(Quest);
    }

    for (UPSQuestBase* Quest : QuestsToAdd)
    {
        if (IsValid(Quest))
        {
            ActiveQuests.Add(Quest);
        }
    }

    QuestsToRemove.Empty();
    QuestsToAdd.Empty();
}
