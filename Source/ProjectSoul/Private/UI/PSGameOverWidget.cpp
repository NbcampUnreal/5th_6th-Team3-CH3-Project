#include "UI/PSGameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainMenuButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonClick);
	ReStartButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::RestartButtonClick);

	UpdateUI();
}

void UPSGameOverWidget::UpdateUI()
{
	UTextBlock* TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalScoreText")));
	UTextBlock* KillCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillCountText")));

	TotalScore->SetText(FText::FromString(FString::Printf(TEXT("TotalScore : 100"))));
	KillCount->SetText(FText::FromString(FString::Printf(TEXT("KillCount : 100"))));
}

void UPSGameOverWidget::MainMenuButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
	RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("MainMenuButtonClick"));
}

void UPSGameOverWidget::RestartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
	RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("RestartButtonClick"));
}
