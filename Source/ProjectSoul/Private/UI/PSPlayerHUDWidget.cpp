#include "UI/PSPlayerHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/PSCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("HPBarContainer")));
	MPBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("MPBarContainer")));
	StaminaBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("StaminaBarContainer")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	
	//USizeBox Init
	if (APSCharacter* PSCharacter = GetCharacter())
	{
		SetHPBarSize(200);
		SetMPBarSize(200);
		SetStaminaBarSize(200);
		/*SetHPBarSize(PSCharacter->MaxHP);
		SetMPBarSize(PSCharacter->MaxMP);
		SetStaminaBarSize(PSCharacter->MaxStamina);*/
	}

	//PlayerBar Init
	SetHPPersent(1.0f);
	SetMPPersent(1.0f);
	SetStaminaPersent(1.0f);

	LockOnImage->SetVisibility(ESlateVisibility::Hidden);
}

//called from the player's TakeDamage() ?
void UPSPlayerHUDWidget::UpdatePlayerHUD(APSCharacter* PSCharacter)
{
	if (APSCharacter* PSCharacter = GetCharacter())
	{
		SetHPPersent(HPBarValue);
		SetMPPersent(MPBarValue);
		SetStaminaPersent(StaminaValue);
		/*SetHPBarSize(PSCharacter->CurrentHP / PSCharacter->MaxHP);
		SetMPBarSize(PSCharacter->CurrentMP / PSCharacter->MaxMP);
		SetStaminaBarSize(PSCharacter->CurrentStamina / PSCharacter->MaxStamina)*/

		SetHPBarSize(HPBarContainerXSize);
		SetMPBarSize(MPBarContainerXSize);
		SetStaminaBarSize(StaminaBarContainerXSize);
		/*SetHPBarSize(PSCharacter->MaxHP);
		SetMPBarSize(PSCharacter->MaxMP);
		SetStaminaBarSize(PSCharacter->MaxStamina)*/
	}
}

void UPSPlayerHUDWidget::SetHPPersent(float HPPersent)
{
	HPBar->SetPercent(FMath::Clamp(HPPersent, 0.0f, 1.0f));
}

void UPSPlayerHUDWidget::SetMPPersent(float MPPersent)
{
	MPBar->SetPercent(FMath::Clamp(MPPersent, 0.0f, 1.0f));
}

void UPSPlayerHUDWidget::SetStaminaPersent(float StaminaPersent)
{
	StaminaBar->SetPercent(FMath::Clamp(StaminaPersent, 0.0f, 1.0f));
}

void UPSPlayerHUDWidget::SetHPBarSize(int MaxHP)
{
	HPBarContainer->SetWidthOverride(MaxHP * 2);
}

void UPSPlayerHUDWidget::SetMPBarSize(int MaxMP)
{
	MPBarContainer->SetWidthOverride(MaxMP * 2);
}

void UPSPlayerHUDWidget::SetStaminaBarSize(int MaxStamina)
{
	StaminaBarContainer->SetWidthOverride(MaxStamina * 2);
}

//player Finde Delegate add
void UPSPlayerHUDWidget::ShowLockOn()
{
	LockOnImage->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(
		LockOnPositionHandle,
		this,
		&UPSPlayerHUDWidget::UpdateLockOnPosition,
		0.05f,
		true
	);
}

void UPSPlayerHUDWidget::HiddenLockOn()
{
	LockOnImage->SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetTimerManager().ClearTimer(LockOnPositionHandle);
}

void UPSPlayerHUDWidget::UpdateLockOnPosition()
{
	if (AActor* Monster = GetCharacter()->GetCurrentTarget())
	{

		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			FVector MonsterWorldLocation = Monster->GetActorLocation();
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
