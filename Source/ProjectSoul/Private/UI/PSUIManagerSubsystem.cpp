#include "UI/PSUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"

UPSUIManagerSubsystem::UPSUIManagerSubsystem()
{
	MainMenuWidgetClass = nullptr;
	MainMenuWidgetInstance = nullptr;
	PlayerHUDWidgetClass = nullptr;
	PlayerHUDWidgetInstance = nullptr;
	MonsterWidgetClass = nullptr;
	MonsterWidgetInstance = nullptr;
	CurrentWidgetInstance = nullptr;

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
	static ConstructorHelpers::FClassFinder<UUserWidget> MonsterHPWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSMonsterWidget.WBP_PSMonsterWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		MonsterWidgetClass = PlayerHUDWidgetBPClass.Class;
	}
}

void UPSUIManagerSubsystem::ShowCurrentWidget()
{
	SetCurrentWidget();
	CurrentWidgetInstance->AddToViewport();
}

void UPSUIManagerSubsystem::HideCurrentWidget()
{
	CurrentWidgetInstance->RemoveFromParent();
}

void UPSUIManagerSubsystem::SetCurrentWidget()
{
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		if (!MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
		}
		CurrentWidgetInstance = MainMenuWidgetInstance;
	}
	else
	{
		if (!PlayerHUDWidgetInstance)
		{
			PlayerHUDWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), PlayerHUDWidgetClass);
		}
		CurrentWidgetInstance = PlayerHUDWidgetInstance;
	}
}
