#include "Gameplay/PSGameModeBase.h"
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
}

void APSGameModeBase::StartGame()
{
    bIsGamePlaying = true;
    bIsGameOver = false;

    UE_LOG(LogTemp, Warning, TEXT("GameStart"));

}

void APSGameModeBase::EndGame()
{
    if (bIsGameOver)
    {
        return;
    }

    bIsGamePlaying = false;
    bIsGameOver = true;

    UE_LOG(LogTemp, Warning, TEXT("GameOver"));

    FTimerHandle RestartTimer;
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APSGameModeBase::RestartGame, 3.0f, false);
}

void APSGameModeBase::RestartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("RestartGame"));

    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
