#include "Structs/FStat.h"

FStat::FStat() :
    CurrentValue(0.0f),
    MaxValue(0.0f)
{
}

float FStat::GetCurrent() const
{
    return CurrentValue;
}

float FStat::GetMax() const
{
    return MaxValue;
}

void FStat::SetCurrent(float NewValue)
{
    CurrentValue = FMath::Clamp(NewValue, 0.0f, MaxValue);
}

void FStat::SetMax(float NewMax)
{
    MaxValue = FMath::Max(NewMax, 0.0f);
    CurrentValue = FMath::Clamp(CurrentValue, 0.0f, MaxValue);
}

void FStat::AdjustValue(float Delta)
{
    SetCurrent(CurrentValue + Delta);
}

void FStat::RestoreFull()
{
    CurrentValue = MaxValue;
}

bool FStat::IsZero() const
{
    return FMath::IsNearlyZero(CurrentValue);
}

float FStat::GetPercent() const
{
    if (FMath::IsNearlyZero(MaxValue))
    {
        return 0.0f;
    }

    return CurrentValue / MaxValue;
}