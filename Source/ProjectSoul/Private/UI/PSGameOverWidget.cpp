#include "UI/PSGameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSGameStateBase.h"

void UPSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainMenuButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonClick);
	ReStartButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::RestartButtonClick);
}

void UPSGameOverWidget::NativePreConstruct()
{
	UpdateUI();
}

void UPSGameOverWidget::UpdateUI()
{
	TotalScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalScoreText")));
	ClearOrDieText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ClearOrDieText")));

	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase)
	{
		TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("TotalScore : %d"), GameStateBase->CurrentScore)));
	}
}

void UPSGameOverWidget::MainMenuButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
	RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("MainMenuButtonClick"));
}

void UPSGameOverWidget::RestartButtonClick()
{
	APSGameModeBase* GameModeBase = Cast<APSGameModeBase>(GetWorld()->GetAuthGameMode());
	GameModeBase->RestartGame();
	//UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
	RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("RestartButtonClick"));
}
