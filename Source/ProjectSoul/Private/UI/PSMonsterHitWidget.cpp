#include "UI/PSMonsterHitWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPSMonsterHitWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TargetMonster = nullptr;
	bIsAddToViewport = false;
}

void UPSMonsterHitWidget::SetDamageText(int Damage)
{
	UTextBlock* TextBlock = Cast<UTextBlock>(DamageText);
	TextBlock->SetText(FText::FromString(FString::Printf(TEXT("%d"), Damage)));
}

void UPSMonsterHitWidget::UpdateHitPosition()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	FVector MonsterLocation = TargetMonster->GetActorLocation();
	FVector2D ScreenPosition;
	PC->ProjectWorldLocationToScreen(MonsterLocation, ScreenPosition);

	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	ScreenPosition /= ViewportScale;

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HitCanvasPanel->Slot))
	{
		CanvasSlot->SetPosition(ScreenPosition);

		if (!bIsAddToViewport)
		{
			AddToViewport();
			bIsAddToViewport = true;
		}
	}
}


void UPSMonsterHitWidget::ShowHitWidget(AActor* Monster, float Damage)
{
	TargetMonster = Monster;
	SetDamageText(Damage);

	GetWorld()->GetTimerManager().SetTimer(
		HitPositionTimer,
		this,
		&UPSMonsterHitWidget::UpdateHitPosition,
		0.02f,
		true
	);

	GetWorld()->GetTimerManager().SetTimer(
		HitEndTimer,
		this,
		&UPSMonsterHitWidget::HiddenHitWidget,
		0.5f
	);
}

void UPSMonsterHitWidget::HiddenHitWidget()
{
	RemoveFromParent();
	TargetMonster = nullptr;
	GetWorld()->GetTimerManager().ClearTimer(HitPositionTimer);
	GetWorld()->GetTimerManager().ClearTimer(HitEndTimer);
}
