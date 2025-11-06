#include "UI/PSMainMenuWidget.h"
#include "UI/PSUIManagerSubsystem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UPSMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::StartButtonClick);
	StartButton->OnHovered.AddDynamic(this, &UPSMainMenuWidget::StartButtonHovered);
	StartButton->OnUnhovered.AddDynamic(this, &UPSMainMenuWidget::StartButtonUnHovered);

	EndButton->OnClicked.AddDynamic(this, &UPSMainMenuWidget::EndButtonClick);
	EndButton->OnHovered.AddDynamic(this, &UPSMainMenuWidget::EndButtonHovered);
	EndButton->OnUnhovered.AddDynamic(this, &UPSMainMenuWidget::EndButtonUnHovered);
}

void UPSMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StartButtonText->SetColorAndOpacity(FColor::White);
	EndButtonText->SetColorAndOpacity(FColor::White);
}

void UPSMainMenuWidget::StartButtonClick()
{
	GetGameInstance()->GetSubsystem<UPSUIManagerSubsystem>()->LevelLoading("Demonstration");
}

void UPSMainMenuWidget::EndButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UPSMainMenuWidget::StartButtonHovered()
{
	StartButtonText->SetColorAndOpacity(FColor::Yellow);
}

void UPSMainMenuWidget::StartButtonUnHovered()
{
	StartButtonText->SetColorAndOpacity(FColor::White);
}

void UPSMainMenuWidget::EndButtonHovered()
{
	EndButtonText->SetColorAndOpacity(FColor::Yellow);
}

void UPSMainMenuWidget::EndButtonUnHovered()
{
	EndButtonText->SetColorAndOpacity(FColor::White);
}

