#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSGameStateBase.h"
#include "Gameplay/PSAudioManagerSubsystem.h"
#include "Gameplay/PSPlayerController.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIcontroller.h"
#include "EngineUtils.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UI/PSUIManagerSubsystem.h"
#include "Quest/PSQuestManagerSubsystem.h"
#include "Character/PSCharacter.h"

APSGameModeBase::APSGameModeBase()
{
    bIsGamePlaying = false;
    bIsGameOver = false;
}

void APSGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSEnemy::StaticClass(), FoundEnemies);

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->SetRemainingEnemies(FoundEnemies.Num());
    }

    if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
    {
        Audio->PlayBGM("Default", 0.4f);
    }

    StartGame();
}


void APSGameModeBase::StartGame()
{
    bIsGamePlaying = true;
    bIsGameOver = false;

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->bIsGamePlaying = true;
        PSState->bIsGameOver = false;
        PSState->bIsGameClear = false;
    }

    if (UGameInstance* GameInstance = GetGameInstance())
    {
        FString CurrentMapName = GetWorld()->GetMapName();
        if (CurrentMapName.Contains("Demonstration"))
        {
            if (UPSQuestManagerSubsystem* QuestManager = GameInstance->GetSubsystem<UPSQuestManagerSubsystem>())
            {
                QuestManager->QuestInit();
            }
        }
        
        if (UPSUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UPSUIManagerSubsystem>())
        {
            if (CurrentMapName.Contains("Demonstration"))
            {
                UIManager->QuestUIInit();
            }
            UIManager->ShowCurrentWidget();
        }
    }
}

void APSGameModeBase::EndGame(bool bIsClear)
{
    if (bIsGameOver)
        return;

    if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
    {
        Audio->StopBGM();
    }

    bIsGamePlaying = false;
    bIsGameOver = true;

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->bIsGamePlaying = false;
        PSState->bIsGameOver = true;
        PSState->bIsGameClear = bIsClear;
    }

	StopAIController();
	StopPlayerInput();

    if (UGameInstance* GameInstance = GetGameInstance())
    {
        if (UPSUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UPSUIManagerSubsystem>())
        {
            UIManager->ShowGameOverUI();
        }
    }
}

void APSGameModeBase::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APSGameModeBase::AddPlayerScore(int32 Amount)
{
    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState && PSState->bIsGamePlaying)
    {
        PSState->AddScore(Amount);
    }
}

void APSGameModeBase::OnEnemyKilled(int32 EnemyScore)
{
    AddPlayerScore(EnemyScore);

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->DecreaseEnemyCount();
    }

    CheckCondition();
}

void APSGameModeBase::OnPlayerKilled()
{
    UE_LOG(LogTemp, Warning, TEXT("Player Dead - Game Over"));
    if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
    {
        Audio->PlayGameOverSFX();
    }

    EndGame(false);
}

void APSGameModeBase::OnBossKilled()
{
    UE_LOG(LogTemp, Warning, TEXT("Boss Dead - Game Clear"));
    if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
    {
        Audio->PlayGameClearSFX();
    }

    EndGame(true);
}

void APSGameModeBase::CheckCondition()
{
    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState && PSState->GetRemainingEnemies() <= 0)
    {
        OnAllEnemiesDead.Broadcast();
    }
}

void APSGameModeBase::StopAIController()
{
    UWorld* World = GetWorld();
    if (!World) return;
    for (TActorIterator<APSEnemyAIController> It(World); It; ++It)
    {
        APSEnemyAIController* AICon = *It;
        if (AICon && AICon->BrainComponent)
        {
            AICon->BrainComponent->StopLogic(TEXT("Game Over"));
        }
    }
}

void APSGameModeBase::StopPlayerInput()
{
    if (APlayerController* PC = (UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->SetCinematicMode(true, false, false, true, true);
        PC->FlushPressedKeys();
    }
}
