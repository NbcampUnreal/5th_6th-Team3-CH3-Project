#include "UI/PSGameOverWidget.h"
#include "UI/PSUIManagerSubsystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Gameplay/PSGameModeBase.h"
#include "Gameplay/PSGameStateBase.h"

void UPSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	GameOverFadeInTime = 3.0f;

	MainMenuButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonClick);
	MainMenuButton->OnHovered.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonHovered);
	MainMenuButton->OnUnhovered.AddDynamic(this, &UPSGameOverWidget::MainMenuButtonUnHovered);

	ReStartButton->OnClicked.AddDynamic(this, &UPSGameOverWidget::RestartButtonClick);
	ReStartButton->OnHovered.AddDynamic(this, &UPSGameOverWidget::RestartButtonHovered);
	ReStartButton->OnUnhovered.AddDynamic(this, &UPSGameOverWidget::RestartButtonUnHovered);
}

void UPSGameOverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	MainMenuButtonText->SetColorAndOpacity(FColor::White);
	ReStartButtonText->SetColorAndOpacity(FColor::White);

	UpdateUI();
}

void UPSGameOverWidget::UpdateUI()
{
	APSGameStateBase* GameStateBase = Cast<APSGameStateBase>(GetWorld()->GetGameState());
	if (GameStateBase)
	{
		TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("TotalScore : %d"), GameStateBase->CurrentScore)));
	}

	if (APSGameStateBase* GameState = GetWorld()->GetGameState<APSGameStateBase>())
	{
		if (GameState->bIsGameClear) 
		{
			ClearOrDieText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
			ClearOrDieText->SetText(FText::FromString(FString::Printf(TEXT("Game Clear"))));
		}
		else
		{
			ClearOrDieText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			ClearOrDieText->SetText(FText::FromString(FString::Printf(TEXT("YOU DIED"))));
		}
	}
}

void UPSGameOverWidget::WidgetFadeIn()
{
	SetRenderOpacity(0.0f);
	MainMenuButton->SetVisibility(ESlateVisibility::Hidden);
	ReStartButton->SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetTimerManager().SetTimer(
		GameOverFadeInTimer,
		[this]()
		{
			float CurrentOpacity = GetRenderOpacity();
			CurrentOpacity += 0.02f / GameOverFadeInTime;
			CurrentOpacity = FMath::Clamp(CurrentOpacity, 0.f, 1.f);
			SetRenderOpacity(CurrentOpacity);

			if (CurrentOpacity >= 1)
			{
				MainMenuButton->SetVisibility(ESlateVisibility::Visible);
				ReStartButton->SetVisibility(ESlateVisibility::Visible);

				GetWorld()->GetTimerManager().ClearTimer(GameOverFadeInTimer);
			}
		},
		0.02f,
		true,
		2.0f
	);
}

void UPSGameOverWidget::MainMenuButtonClick()
{
	GetGameInstance()->GetSubsystem<UPSUIManagerSubsystem>()->LevelLoading("MenuLevel");
}

void UPSGameOverWidget::RestartButtonClick()
{
	GetGameInstance()->GetSubsystem<UPSUIManagerSubsystem>()->LevelLoading("Demonstration");
}

void UPSGameOverWidget::MainMenuButtonHovered()
{
	MainMenuButtonText->SetColorAndOpacity(FColor::Yellow);
}

void UPSGameOverWidget::MainMenuButtonUnHovered()
{
	MainMenuButtonText->SetColorAndOpacity(FColor::White);
}

void UPSGameOverWidget::RestartButtonHovered()
{
	ReStartButtonText->SetColorAndOpacity(FColor::Yellow);
}

void UPSGameOverWidget::RestartButtonUnHovered()
{
	ReStartButtonText->SetColorAndOpacity(FColor::White);
}

