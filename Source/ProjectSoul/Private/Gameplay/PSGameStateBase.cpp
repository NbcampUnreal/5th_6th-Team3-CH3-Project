#include "Gameplay/PSGameStateBase.h"

APSGameStateBase::APSGameStateBase()
{
    bIsGamePlaying = false;
    bIsGameOver = false;
    bIsGameClear = false;
    CurrentScore = 0;
    RemainingEnemies = 0;
}

void APSGameStateBase::AddScore(int32 Amount)
{
    CurrentScore += Amount;

    UE_LOG(LogTemp, Warning, TEXT("Add Score: +%d (Current Score: %d)"), Amount, CurrentScore);
}

void APSGameStateBase::DecreaseEnemyCount()
{
    if (RemainingEnemies > 0)
    {
        RemainingEnemies--;
        UE_LOG(LogTemp, Warning, TEXT("Remaining Enemies: %d"), RemainingEnemies);
	}
}

int32 APSGameStateBase::GetRemainingEnemies() const
{
    return RemainingEnemies;
}

void APSGameStateBase::SetRemainingEnemies(int32 Count)
{
	RemainingEnemies = Count;
}
