#include "UI/PSPlayerHUDWidget.h"
#include "UI/PSMonsterHitWidget.h"
#include "UI/PSTriggerActor.h"
#include "UI/PSQuestTextWidget.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Character/PSCharacter.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSBossEnemy.h"
#include "Gameplay/PSGameStateBase.h"
#include "Quest/PSQuestManagerSubsystem.h"
#include "Quest/PSQuestBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPSPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SizeBoxMultiplier = 3.0f;
	HiddenBossStatusWidget();
	//RunTime Load
	UClass* BP_MonsterHitWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/WBP_PSMonsterHitWidget.WBP_PSMonsterHitWidget_C"));
	if (BP_MonsterHitWidgetClass)
	{
		MonsterHitWidgetClass = BP_MonsterHitWidgetClass;
	}
	UClass* BP_QuestTextWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/WBP_PSQuestTextWidget.WBP_PSQuestTextWidget_C"));
	if (BP_QuestTextWidgetClass)
	{
		QuestTextWidgetClass = BP_QuestTextWidgetClass;
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
			Enemy->OnEnemyDie.AddDynamic(this, &UPSPlayerHUDWidget::QuestUpdateDelegate);
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

	if (HPBarBackImageContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		HPBarBackImageContainer->SetWidthOverride(NewWidth + 10);
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

	if (MPBarBackImageContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		MPBarBackImageContainer->SetWidthOverride(NewWidth + 10);
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

	if (StaminaBarBackImageContainer)
	{
		float NewWidth = MaxValue * SizeBoxMultiplier;
		StaminaBarBackImageContainer->SetWidthOverride(NewWidth + 10);
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

void UPSPlayerHUDWidget::ShowBossStatusWidget(AActor* BossMonster, bool bIsAreaIn)
{
	if (bIsAreaIn)
	{
		BossStatsVerticalBox->SetVisibility(ESlateVisibility::Visible);
		if (BossMonster)
		{
			BossName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *BossMonster->GetName())));
			BossHPBar->SetPercent(1.0f);
		}
	}
	else
	{
		BossStatsVerticalBox->SetVisibility(ESlateVisibility::Hidden);
	}
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

//APSEnemy : TakeDamage : OnEnemyDie Deldgate call
void UPSPlayerHUDWidget::QuestUpdateDelegate(AActor* UnUsed)
{
	QuestUpdate();
}
//UPSUIManagerSubsystem test
void UPSPlayerHUDWidget::QuestUpdate()
{
	UPSQuestManagerSubsystem* QuestManagerSubsystem = GetGameInstance()->GetSubsystem<UPSQuestManagerSubsystem>();
	if (QuestManagerSubsystem->bIsQuestInit == false)
	{
		QuestManagerSubsystem->QuestInit();
		QuestManagerSubsystem->bIsQuestInit = true;
	}
	QuestManagerSubsystem->UpdateQuest(QuestMap);

	for (int i = 0; i < QuestManagerSubsystem->ActiveQuests.Num(); i++)
	{
		FName QuestName = QuestManagerSubsystem->ActiveQuests[i]->GetQuestName();
		if (QuestMap.Find(QuestName) == nullptr)
		{
			CreateQuestText(QuestName);
		}

		if (QuestMap.Num() > 0)
		{
			UTextBlock* TextBlock = Cast<UTextBlock>(QuestMap[QuestName]->GetWidgetFromName(TEXT("QuestText")));
			TextBlock->SetText(FText::FromString(QuestManagerSubsystem->ActiveQuests[i]->QuestTextUpdate()));
		}
	}
}

void UPSPlayerHUDWidget::CreateQuestText(FName QuestName)
{
	if (UPSQuestTextWidget* QuestTextWidget = CreateWidget<UPSQuestTextWidget>(this, QuestTextWidgetClass))
	{
		if (QuestTextWidget)
		{
			UVerticalBox* QuestsBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("QuestBox")));
			if (QuestsBox)
			{
				QuestsBox->AddChild(QuestTextWidget);
				QuestMap.Add(QuestName,QuestTextWidget);
			}
		}
	}
}

void UPSPlayerHUDWidget::DeleteQuestText()
{

}
