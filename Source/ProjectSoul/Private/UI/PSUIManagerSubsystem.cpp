#include "UI/PSUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UI/PSPlayerHUDWidget.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSMainMenuWidget.WBP_PSMainMenuWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSPlayerHUDWidget.WBP_PSPlayerHUDWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		PlayerHUDWidgetClass = PlayerHUDWidgetBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSGameOverWidget.WBP_PSGameOverWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetBPClass.Class;
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
	}
}
