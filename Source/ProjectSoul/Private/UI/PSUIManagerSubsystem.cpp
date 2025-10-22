#include "UI/PSUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"

UPSUIManagerSubsystem::UPSUIManagerSubsystem()
{
	CurrentWidgetClass = nullptr;
	CurrentWidgetInstance = nullptr;


	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSMainMenuWidget.WBP_PSMainMenuWidget_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetBPClass.Class;
		MainMenuWidgetInstance = nullptr;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDWidgetBPClass(TEXT("/Game/Blueprints/UI/WBP_PSPlayerHUD.WBP_PSPlayerHUD_C"));
	if (MainMenuWidgetBPClass.Succeeded())
	{
		PlayerHUDWidgetClass = PlayerHUDWidgetBPClass.Class;
		PlayerHUDWidgetInstance = nullptr;
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

FString UPSUIManagerSubsystem::GetCurretnWidget()
{
	return CurrentWidgetInstance->GetName();
}

void UPSUIManagerSubsystem::SetCurrentWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Function In"));
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuLevel In"));
		CurrentWidgetClass = MainMenuWidgetClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BasicLevel In"));
		CurrentWidgetClass = PlayerHUDWidgetClass;
	}
	CurrentWidgetInstance = CreateWidget(GetWorld()->GetFirstPlayerController(), CurrentWidgetClass);
}

void UPSUIManagerSubsystem::UpdateUI()
{
	//CurrentWidget->UpdateCanTick();
}

