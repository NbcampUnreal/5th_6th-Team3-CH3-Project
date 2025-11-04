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

void UPSQuestManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    //StartQuests
    UPSQuestBase* MonsterKillQuest = NewObject<UPSMonsterKillQuest>(this);

    if (MonsterKillQuest)
    {
        ActiveQuests.Add(MonsterKillQuest);
    }

}
//UPSPlayerHUDWidget : QuestUpdate call
void UPSQuestManagerSubsystem::QuestInit()
{
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

void UPSQuestManagerSubsystem::UpdateQuest(TMap<FName, UPSQuestTextWidget*> QuestWidget)
{
    UE_LOG(LogTemp, Warning, TEXT("UPSQuestManagerSubsystem : UpdateTextQuest call"));
    for (int i = ActiveQuests.Num() - 1; i >= 0; i--)
    {
        CheckQuest = ActiveQuests[i];
        if (CheckQuest->ClearCondition())
        {
            QuestWidget[CheckQuest->GetQuestName()]->RemoveFromParent();
            QuestWidget.Remove(CheckQuest->GetQuestName());

            if (CheckQuest->GetNextQuest() != nullptr)
            {
                ActiveQuests.Add(CheckQuest->GetNextQuest());
            }

            ActiveQuests.Remove(ActiveQuests[i]);
        }
    }
}

