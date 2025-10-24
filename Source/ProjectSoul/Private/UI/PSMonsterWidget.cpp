#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Enemy/PSEnemy.h"
#include "Character/PSCharacter.h"
#include "Components/WidgetComponent.h" 

void UPSMonsterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPSMonsterWidget::UpdateMonsterHP(float Percent)
{
	HPBar->SetPercent(Percent);
}
  
//player Finde Delegate add??
void UPSMonsterWidget::ShowMonsterHP()
{
	HPBar->SetVisibility(ESlateVisibility::Visible);
}

void UPSMonsterWidget::HiddenMonsterHP()
{
	HPBar->SetVisibility(ESlateVisibility::Hidden);
}

void UPSMonsterWidget::SetMonsterHP(UWidgetComponent* OverheadWidget, APSEnemy* Monster)
{
	//if (UUserWidget* WidgetInstance = OverheadWidget->GetUserWidgetObject())
	//{
	//	WidgetInstance->SetVisibility(ESlateVisibility::Visible);

	//	if (UProgressBar* HPBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("HPBar"))))
	//	{
	//		//const float HPPercent = (Monster->HP > 0.f) ? Monster->HP / Monster->MaxHP : 0.f;
	//		HPBar->SetPercent(1.0f);

	//		/*if (HPPercent < 0.3f)
	//		{
	//			HPBar->SetFillColorAndOpacity(FLinearColor::Red);
	//		}*/
	//	}
	//}
}

APSCharacter* UPSMonsterWidget::GetCharacter()
{
	if (APlayerController* PlayerContrller = GetWorld()->GetFirstPlayerController())
	{
		if (APSCharacter* PSCharacter = Cast<APSCharacter>(PlayerContrller->GetPawn()))
		{
			return PSCharacter;
		}
	}

	return nullptr;
}
