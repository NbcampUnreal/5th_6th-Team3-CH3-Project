#include "UI/PSMainMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UPSMainMenuWidget::NativeOnInitialized()
{
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	EndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	StartButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::StartButtonClick);
	EndButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::EndButtonClick);
}

void UPSMainMenuWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
	RemoveFromParent();
}

void UPSMainMenuWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
	
