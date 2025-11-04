#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSGameStateBase.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIcontroller.h"
#include "EngineUtils.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UI/PSUIManagerSubsystem.h"
#include "Gameplay/PSAudioManagerSubsystem.h"

APSGameModeBase::APSGameModeBase()
{
    bIsGamePlaying = false;
    bIsGameOver = false;
}

void APSGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    StartGame();

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSEnemy::StaticClass(), FoundEnemies);

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->RemainingEnemies = FoundEnemies.Num();
        UE_LOG(LogTemp, Warning, TEXT("Enemy Count: %d"), PSState->RemainingEnemies);
    }

    if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
    {
        Audio->PlayBGM(0.4f);
    }
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

    UE_LOG(LogTemp, Warning, TEXT("Game Start"));
    if (UGameInstance* GameInstance = GetGameInstance())
    {
        if (UPSUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UPSUIManagerSubsystem>())
        {
            OnGameOver.AddDynamic(UIManager, &UPSUIManagerSubsystem::ShowCurrentWidget);
        }
    }
    OnGameOver.Broadcast(bIsGameOver);
}

void APSGameModeBase::EndGame(bool bIsClear)
{
    if (bIsGameOver)
        return;

    bIsGamePlaying = false;
    bIsGameOver = true;

    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState)
    {
        PSState->bIsGamePlaying = false;
        PSState->bIsGameOver = true;
        PSState->bIsGameClear = bIsClear;
    }
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
    UE_LOG(LogTemp, Warning, TEXT("Game Over | Result: %s"), bIsClear ? TEXT("CLEAR") : TEXT("FAIL"));
    OnGameOver.Broadcast(bIsGameOver);

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
        PSState->RemainingEnemies--;
        UE_LOG(LogTemp, Warning, TEXT("Enemy Dead | Remaining: %d"), PSState->RemainingEnemies);
    }

    CheckClearCondition();
}

void APSGameModeBase::OnPlayerKilled()
{
    UE_LOG(LogTemp, Warning, TEXT("Player Dead - Game Over"));
    EndGame(false);
}

void APSGameModeBase::CheckClearCondition()
{
    APSGameStateBase* PSState = GetGameState<APSGameStateBase>();
    if (PSState && PSState->RemainingEnemies <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("All Enemies Dead - Mission Clear!"));
        EndGame(true);
    }
}
