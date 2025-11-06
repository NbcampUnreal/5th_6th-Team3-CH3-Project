#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"

void UPSMonsterWidget::UpdateMonsterHP(float Percent)
{
	if (Percent >= 0)
	{
		HPBar->SetPercent(Percent);
	}
}
