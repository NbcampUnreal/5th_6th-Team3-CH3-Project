#include "UI/PSGameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainMenuButton = Cast<UButton>(GetWidgetFromName(TEXT("MainMenuButton")));
	ReStartButton = Cast<UButton>(GetWidgetFromName(TEXT("ReStartButton")));
	TotalScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalScoreText")));
	KillCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillCountText")));

	MainMenuButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonClick);
	ReStartButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::RestartButtonClick);
}

void UPSGameOverWidget::UpdateUI()
{

}

void UPSGameOverWidget::MainMenuButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("MainMenuButtonClick"));
}

void UPSGameOverWidget::RestartButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("RestartButtonClick"));
}
