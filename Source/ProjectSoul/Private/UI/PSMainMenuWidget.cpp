#include "UI/PSMainMenuWidget.h"
#include "UI/PSUIManagerSubsystem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UPSMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::StartButtonClick);
	EndButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::EndButtonClick);
}

void UPSMainMenuWidget::StartButtonClick()
{
	GetGameInstance()->GetSubsystem<UPSUIManagerSubsystem>()->LevelLoading("Demonstration");
	RemoveFromParent();
}

void UPSMainMenuWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

