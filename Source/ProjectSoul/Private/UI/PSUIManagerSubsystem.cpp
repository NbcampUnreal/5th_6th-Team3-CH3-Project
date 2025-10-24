#include "UI/PSUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UI/PSPlayerHUDWidget.h"

UPSUIManagerSubsystem::UPSUIManagerSubsystem()
{
	MainMenuWidgetClass = nullptr;
	MainMenuWidgetInstance = nullptr;
	PlayerHUDWidgetClass = nullptr;
	PlayerHUDWidgetInstance = nullptr;
	GameOverWidgetClass = nullptr;
	GameOverWidgetInstance = nullptr;
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
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSGameOverWidget.WBP_PSGameOverWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetBPClass.Class;
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

void UPSUIManagerSubsystem::ShowLockOn(AActor* LockOnMonster)
{
	GetWorld()->GetFirstPlayerController()->GetOwner();

	UPSPlayerHUDWidget* PlayerHUD = Cast<UPSPlayerHUDWidget>(PlayerHUDWidgetInstance);
	PlayerHUD->ShowLockOn(LockOnMonster);
}

void UPSUIManagerSubsystem::HiddenLockOn()
{
	UPSPlayerHUDWidget* PlayerHUD = Cast<UPSPlayerHUDWidget>(PlayerHUDWidgetInstance);
	PlayerHUD->HiddenLockOn();
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
		if (MainMenuWidgetInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainMenu Create Success"));
			CurrentWidgetInstance = MainMenuWidgetInstance;
		}
	}
	else
	{
		if (!PlayerHUDWidgetInstance)
		{
			PlayerHUDWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), PlayerHUDWidgetClass);
			
		}
		if (PlayerHUDWidgetInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerHUD Create Success"));
			CurrentWidgetInstance = PlayerHUDWidgetInstance;
		}
	}
}

void UPSUIManagerSubsystem::ShowMainMenuUI()
{
	MainMenuWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
	MainMenuWidgetInstance->AddToViewport();
}

void UPSUIManagerSubsystem::ShowPlayerHUD()
{
	PlayerHUDWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), PlayerHUDWidgetClass);
	PlayerHUDWidgetInstance->AddToViewport();
}

void UPSUIManagerSubsystem::ShowGameOverUI()
{
	GameOverWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), GameOverWidgetClass);
	GameOverWidgetInstance->AddToViewport();
}
