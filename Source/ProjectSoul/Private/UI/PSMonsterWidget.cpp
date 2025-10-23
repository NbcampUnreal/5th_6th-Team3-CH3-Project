#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"

void UPSMonsterWidget::NativeOnInitialized()
{
	MonsterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHPBar")));
}

void UPSMonsterWidget::
