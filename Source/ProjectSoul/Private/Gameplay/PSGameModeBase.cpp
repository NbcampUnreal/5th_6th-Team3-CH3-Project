#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

APSGameModeBase::APSGameModeBase()
{
    bIsGamePlaying = false;
    bIsGameOver = false;
    RestartDelay = 3.0f;
}

void APSGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    StartGame();

    FTimerHandle ScoreTimer;
    GetWorldTimerManager().SetTimer(ScoreTimer, [this]()
        {
            AddPlayerScore(100);
        }, 3.0f, false);
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
    }

    UE_LOG(LogTemp, Warning, TEXT("GameStart)"));
}

void APSGameModeBase::EndGame()
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
    }

    UE_LOG(LogTemp, Warning, TEXT("GameOver"));

    FTimerHandle RestartTimer;
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APSGameModeBase::RestartGame, RestartDelay, false);
}

void APSGameModeBase::RestartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("ReStart"));
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
