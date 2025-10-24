#include "Structs/FEnemyStats.h"

FEnemyStats::FEnemyStats()
{
	Health = FStat();
	Stamina = FStat();
}

void FEnemyStats::RestoreAll()
{
	Health.RestoreFull();
	Stamina.RestoreFull();
}

float FEnemyStats::GetHealthPercent() const
{
	return Health.GetPercent();
}

float FEnemyStats::GetStaminaPercent() const
{
	return Stamina.GetPercent();
}