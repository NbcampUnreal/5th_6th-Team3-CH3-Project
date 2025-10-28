#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"

//call from monster TakeDamege()
void UPSMonsterWidget::UpdateMonsterHP(float Percent)
{
	if (Percent >= 0)
	{
		HPBar->SetPercent(Percent);
	}
}
