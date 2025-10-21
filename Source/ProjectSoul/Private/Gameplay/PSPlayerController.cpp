#include "Gameplay/PSPlayerController.h"
#include "Blueprint/UserWidget.h"

APSPlayerController::APSPlayerController()
{
	MainMenuWidgetClass = nullptr;
	MainMenuWidgetInstance = nullptr;

}

void APSPlayerController::BeginPlay()
{
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu();
	}
}

void APSPlayerController::ShowMainMenu()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget(this, MainMenuWidgetClass);

		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
	}
}
