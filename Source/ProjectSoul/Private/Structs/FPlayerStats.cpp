#include "Structs/FPlayerStats.h"

FPlayerStats::FPlayerStats()
{
    Health = FStat();
    Mana = FStat();
	Stamina = FStat();
}

void FPlayerStats::RestoreAll()
{
    Health.RestoreFull();
    Mana.RestoreFull();
    Stamina.RestoreFull();
}

float FPlayerStats::GetHealthPercent() const
{
    return Health.GetPercent();
}

float FPlayerStats::GetManaPercent() const
{
    return Mana.GetPercent();
}

float FPlayerStats::GetStaminaPercent() const
{
    return Stamina.GetPercent();
}