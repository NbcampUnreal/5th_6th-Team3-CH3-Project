#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Enemy/PSEnemy.h"

void UPSMonsterWidget::NativeOnInitialized()
{
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}

void UPSMonsterWidget::SetMonsterHP(UWidgetComponent* OverheadWidget, APSEnemy* Monster)
{
	if (UUserWidget* WidgetInstance = OverheadWidget->GetUserWidgetObject())
	{
		WidgetInstance->SetVisibility(ESlateVisibility::Visible);

		if (UProgressBar* HPBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("HPBar"))))
		{
			//const float HPPercent = (Monster->HP > 0.f) ? Monster->HP / Monster->MaxHP : 0.f;
			HPBar->SetPercent(1.0f);

			/*if (HPPercent < 0.3f)
			{
				HPBar->SetFillColorAndOpacity(FLinearColor::Red);
			}*/
		}
	}
}
