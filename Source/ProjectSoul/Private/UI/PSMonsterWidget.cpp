#include "UI/PSMonsterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Character/PSCharacter.h"

void UPSMonsterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	HPBar->SetVisibility(ESlateVisibility::Hidden);
	bLockOn = false;
	TestHP = 1.0f;
}

//call from monster TakeDamege()
void UPSMonsterWidget::UpdateMonsterHP(float Percent)
{

	if (Percent >= 0)
	{
		HPBar->SetPercent(Percent);
		ShowHitMonsterHP();
	}
}

//player Finde Delegate add??
void UPSMonsterWidget::ShowMonsterHP()
{
	bLockOn = true;
	HPBar->SetVisibility(ESlateVisibility::Visible);
}

void UPSMonsterWidget::HiddenMonsterHP()
{
	bLockOn = false;
	HPBar->SetVisibility(ESlateVisibility::Hidden);
}


void UPSMonsterWidget::ShowHitMonsterHP()
{
	HPBar->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(
		ShowMonsterHPTimer,
		this,
		&UPSMonsterWidget::HiddenHitMonsterHP,
		3.0f
	);
}

void UPSMonsterWidget::HiddenHitMonsterHP()
{
	if (!bLockOn)
	{
		HPBar->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetTimerManager().ClearTimer(ShowMonsterHPTimer);
	}
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
