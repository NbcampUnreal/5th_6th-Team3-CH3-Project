#include "UI/PSUIManagerSubsystem.h"
#include "UI/PSPlayerHUDWidget.h"
#include "UI/PSGameOverWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/PSGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UPSUIManagerSubsystem::UPSUIManagerSubsystem()
{
	MainMenuWidgetClass = nullptr;
	MainMenuWidgetInstance = nullptr;
	PlayerHUDWidgetClass = nullptr;
	PlayerHUDWidgetInstance = nullptr;
	GameOverWidgetClass = nullptr;
	GameOverWidgetInstance = nullptr;
	LoadingWidgetClass = nullptr;
	LoadingWidgetInstance = nullptr;

	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSMainMenuWidget.WBP_PSMainMenuWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetBPClass.Class;
	}
	ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSPlayerHUDWidget.WBP_PSPlayerHUDWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		PlayerHUDWidgetClass = PlayerHUDWidgetBPClass.Class;
	}
	ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSGameOverWidget.WBP_PSGameOverWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetBPClass.Class;
	}
	ConstructorHelpers::FClassFinder<UUserWidget> LoadingWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSLoadingWidget.WBP_PSLoadingWidget_C"));
	if (LoadingWidgetBPClass.Succeeded())
	{
		LoadingWidgetClass = LoadingWidgetBPClass.Class;
	}
}

void UPSUIManagerSubsystem::ShowCurrentWidget(bool bIsGameOver)
{
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenuUI();
	}
	else if ( bIsGameOver )
	{
		ShowGameOverUI();
	}
	else 
	{
		ShowPlayerHUD();
	}
}

void UPSUIManagerSubsystem::ShowMainMenuUI()
{
	if (PlayerHUDWidgetInstance)
	{
		PlayerHUDWidgetInstance->RemoveFromParent();
	}
	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->RemoveFromParent();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (!MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance = CreateWidget(PC, MainMenuWidgetClass);
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->AddToViewport();
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}

void UPSUIManagerSubsystem::ShowPlayerHUD()
{
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
	}
	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->RemoveFromParent();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (!PlayerHUDWidgetInstance)
	{
		PlayerHUDWidgetInstance = CreateWidget(PC, PlayerHUDWidgetClass);
	}
	if (PlayerHUDWidgetInstance)
	{
		PlayerHUDWidgetInstance->AddToViewport();
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void UPSUIManagerSubsystem::ShowGameOverUI()
{
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (!GameOverWidgetInstance)
	{
		GameOverWidgetInstance = CreateWidget(PC, GameOverWidgetClass);
	}
	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->AddToViewport();
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());

		UPSGameOverWidget* GameOverWidget = Cast<UPSGameOverWidget>(GameOverWidgetInstance);
		if (GameOverWidget)
		{
			GameOverWidget->WidgetFadeIn();
		}
	}
}

void UPSUIManagerSubsystem::LevelLoading(FName LevelName)
{
	ShowLoadingUI();
	OpenLevelName = LevelName;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OpenLevel");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = __LINE__;
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, false, LatentInfo);
}

void UPSUIManagerSubsystem::ShowLoadingUI()
{
	if (LoadingWidgetInstance == nullptr)
	{
		LoadingWidgetInstance = CreateWidget(GetGameInstance(), LoadingWidgetClass);
	}
	LoadingWidgetInstance->AddToViewport();
}

void UPSUIManagerSubsystem::OpenLevel()
{
	FTimerHandle DelayOpenLevelTimer;
	GetWorld()->GetTimerManager().SetTimer(
		DelayOpenLevelTimer,
		[this]()
		{
			UGameplayStatics::OpenLevel(GetWorld(), OpenLevelName);
		},
		2.0f,
		false
	);
}