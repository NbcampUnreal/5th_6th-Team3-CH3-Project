#include "Gameplay/PSGameStateBase.h"

APSGameStateBase::APSGameStateBase()
{
    bIsGamePlaying = false;
    bIsGameOver = false;
    bIsGameClear = false;
    CurrentScore = 0;
}

void APSGameStateBase::AddScore(int32 Amount)
{
    CurrentScore += Amount;

    UE_LOG(LogTemp, Warning, TEXT("Add Score: +%d (Current Score: %d)"), Amount, CurrentScore);
}
