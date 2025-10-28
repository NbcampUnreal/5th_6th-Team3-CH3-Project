#include "UI/PSPlayerHUDWidget.h"
#include "UI/PSMonsterHitWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/PSCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LockOnTarget = nullptr;
	SizeBoxMultiplier = 3.0f;
	bLockOn = false;

	if (APSCharacter* PSCharacter = GetCharacter())
	{
		PSCharacter->OnHPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateHPBar);
		PSCharacter->OnMPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateMPBar);
		PSCharacter->OnStaminaChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateStaminaBar);
	
		PSCharacter->OnEnemyTarget.AddDynamic(this, &UPSPlayerHUDWidget::ShowLockOn);
	}

	LockOnImage->SetVisibility(ESlateVisibility::Hidden);

	/*static ConstructorHelpers::FClassFinder<UUserWidget> MonsterHitWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSMonsterHitWidget.WBP_PSMonsterHitWidget_C"));
	if (MonsterHitWidgetBPClass.Succeeded())
	{
		MonsterHitWidgetClass = MonsterHitWidgetBPClass.Class;
	}*/
}
//player Delegate add
void UPSPlayerHUDWidget::OnUpdateHPBar(float CurrentValue, float MaxValue)
{
	if (HPBar)
	{
		HPBar->SetPercent(CurrentValue / MaxValue);
	}

	if (HPBarContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		HPBarContainer->SetWidthOverride(NewWidth);
	}
}
//player Delegate add
void UPSPlayerHUDWidget::OnUpdateMPBar(float CurrentValue, float MaxValue)
{
	if (MPBar)
	{
		MPBar->SetPercent(CurrentValue / MaxValue);
	}

	if (MPBarContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		MPBarContainer->SetWidthOverride(NewWidth);
	}
}
//player Delegate add
void UPSPlayerHUDWidget::OnUpdateStaminaBar(float CurrentValue, float MaxValue)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentValue / MaxValue);
	}
	if (StaminaBarContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		StaminaBarContainer->SetWidthOverride(NewWidth);
	}
}
//player Delegate add
void UPSPlayerHUDWidget::ShowLockOn(AActor* CurrentTarget)
{
	if (CurrentTarget)
	{
		bLockOn = true;
		LockOnTarget = CurrentTarget;
		LockOnImage->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(
			LockOnPositionHandle,
			this,
			&UPSPlayerHUDWidget::UpdateLockOnPosition,
			0.125f,
			true
		);
	}
	else
	{
		bLockOn = false;
		HiddenLockOn();
	}
}

void UPSPlayerHUDWidget::HiddenLockOn()
{
	LockOnImage->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().ClearTimer(LockOnPositionHandle);
	LockOnTarget = nullptr;
}


void UPSPlayerHUDWidget::ShowHit(AActor* LockOnMonster)
{
	/*if (LockOnMonster)
	{
		LockOnTarget = LockOnMonster;
		HitImage->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(
			LockOnPositionHandle,
			this,
			&UPSPlayerHUDWidget::UpdateLockOnPosition,
			0.125f,
			true
		);

		GetWorld()->GetTimerManager().SetTimer(
			HitPositionHandle,
			this,
			&UPSPlayerHUDWidget::HiddenHit,
			1.0f,
			false
		);
	}*/
 
	UE_LOG(LogTemp, Warning, TEXT("ShowHit Test"));
	/*APlayerController* PC = GetWorld()->GetFirstPlayerController();

	UPSMonsterHitWidget* HitWidgetInstance = CreateWidget<UPSMonsterHitWidget>(PC, HitWidgetClass);
	HitWidgetInstance->ShowHitWidget(LockOnMonster);*/
}

void UPSPlayerHUDWidget::HiddenHit()
{
	/*HitImage->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().ClearTimer(HitPositionHandle);
	LockOnTarget = nullptr;

	if (!bLockOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(LockOnPositionHandle);
	}*/

}

void UPSPlayerHUDWidget::UpdateLockOnPosition()
{
	if (LockOnTarget)
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			FVector MonsterWorldLocation = LockOnTarget->GetActorLocation();
			FVector2D MonsterScreenLocation;
			PC->ProjectWorldLocationToScreen(MonsterWorldLocation, MonsterScreenLocation);

			float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
			MonsterScreenLocation /= ViewportScale;

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(LockOnImage->Slot))
			{
				CanvasSlot->SetPosition(MonsterScreenLocation);
			}
		}
	}
}

APSCharacter* UPSPlayerHUDWidget::GetCharacter()
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
