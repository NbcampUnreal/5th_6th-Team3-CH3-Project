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
}

void APSGameStateBase::DecreaseEnemyCount()
{
    if (RemainingEnemies > 0)
    {
        RemainingEnemies--;
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
