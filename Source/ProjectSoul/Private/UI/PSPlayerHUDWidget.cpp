#include "UI/PSPlayerHUDWidget.h"
#include "UI/PSMonsterHitWidget.h"
#include "UI/PSTriggerActor.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/PSCharacter.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSBossEnemy.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


void UPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SizeBoxMultiplier = 3.0f;
	HiddenBossStatusWidget();
	//RunTime Load
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/WBP_PSMonsterHitWidget.WBP_PSMonsterHitWidget_C"));
	if (WidgetClass)
	{
		MonsterHitWidgetClass = WidgetClass;
	}
}

void UPSPlayerHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	LockOnTarget = nullptr;
	bLockOn = false;
	LockOnImage->SetVisibility(ESlateVisibility::Hidden);

	if (APSCharacter* PSCharacter = GetCharacter())
	{
		PSCharacter->OnHPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateHPBar);
		PSCharacter->OnMPChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateMPBar);
		PSCharacter->OnStaminaChanged.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateStaminaBar);

		PSCharacter->OnEnemyTarget.AddDynamic(this, &UPSPlayerHUDWidget::ShowLockOnWidget);
	}

	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSEnemy::StaticClass(), FoundEnemies);
	for (AActor* Mosnter : FoundEnemies)
	{
		APSEnemy* Enemy = Cast<APSEnemy>(Mosnter);
		if (Enemy)
		{
			Enemy->OnHit.AddDynamic(this, &UPSPlayerHUDWidget::ShowHitWidget);
			
			if (APSBossEnemy* Boss = Cast<APSBossEnemy>(Enemy))
			{
				Boss->OnHit.AddDynamic(this, &UPSPlayerHUDWidget::OnUpdateBossHPBar);
			}
		}
	}

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), APSTriggerActor::StaticClass()))
	{
		if (APSTriggerActor* TriggerActor = Cast<APSTriggerActor>(Actor))
		{
			TriggerActor->OnTrigger.AddDynamic(this, &UPSPlayerHUDWidget::ShowBossStatusWidget);
		}
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
void UPSPlayerHUDWidget::ShowLockOnWidget(AActor* CurrentTarget)
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
		HiddenLockOnWidget();
	}
}

void UPSPlayerHUDWidget::HiddenLockOnWidget()
{
	LockOnImage->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().ClearTimer(LockOnPositionHandle);
	LockOnTarget = nullptr;
}

//Enemy Delegate add
void UPSPlayerHUDWidget::ShowHitWidget(AActor* LockOnMonster, float Damage)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	UPSMonsterHitWidget* HitWidgetInstance = CreateWidget<UPSMonsterHitWidget>(PC, MonsterHitWidgetClass);
	HitWidgetInstance->ShowHitWidget(LockOnMonster, Damage);
}

void UPSPlayerHUDWidget::ShowBossStatusWidget() 
{
	UE_LOG(LogTemp, Warning, TEXT("ShowBossStatusWidget On"));
	BossStatsVerticalBox->SetVisibility(ESlateVisibility::Visible);
	BossName->SetText(FText::FromString(FString::Printf(TEXT(""))));
	BossHPBar->SetPercent(1.0f);
}

void UPSPlayerHUDWidget::HiddenBossStatusWidget()
{
	BossStatsVerticalBox->SetVisibility(ESlateVisibility::Hidden);
}
//Enemy Delegate add
void UPSPlayerHUDWidget::OnUpdateBossHPBar(AActor* Monster, float Damage)
{
	APSEnemy* BossMonster = Cast<APSEnemy>(Monster);
	if (BossHPBar)
	{
		BossHPBar->SetPercent(BossMonster->GetEnemyStats().GetHealthPercent());
	}
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

