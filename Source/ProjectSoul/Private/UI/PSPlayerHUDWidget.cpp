#include "UI/PSPlayerHUDWidget.h"
#include "UI/PSMonsterHitWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/PSCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Enemy/PSEnemy.h"
#include "Kismet/GameplayStatics.h"

void UPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SizeBoxMultiplier = 3.0f;
	//RunTime Load
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/WBP_PSMonsterHitWidget.WBP_PSMonsterHitWidget_C"));
	if (WidgetClass)
	{
		MonsterHitWidgetClass = WidgetClass;
	}
}

void UPSPlayerHUDWidget::NativePreConstruct()
{
	LockOnTarget = nullptr;
	bLockOn = false;
	LockOnImage->SetVisibility(ESlateVisibility::Hidden);

	if (APSCharacter* PSCharacter = GetCharacter())
	{
		PSCharacter->OnHPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateHPBar);
		PSCharacter->OnMPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateMPBar);
		PSCharacter->OnStaminaChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateStaminaBar);

		PSCharacter->OnEnemyTarget.AddDynamic(this, &UPSPlayerHUDWidget::ShowLockOn);
	}

	APSEnemy* Enemy = Cast<APSEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), APSEnemy::StaticClass()));
	if (Enemy)
	{
		// HUD에 등록 함수 제공
		Enemy->OnHit.AddDynamic(this, &UPSPlayerHUDWidget::ShowHitWidget);
	}
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
			0.02f,
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


void UPSPlayerHUDWidget::ShowHitWidget(AActor* LockOnMonster, float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("ShowHit Test"));
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	UPSMonsterHitWidget* HitWidgetInstance = CreateWidget<UPSMonsterHitWidget>(PC, MonsterHitWidgetClass);
	HitWidgetInstance->ShowHitWidget(LockOnMonster, Damage);
}

void UPSPlayerHUDWidget::HiddenHit()
{

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

