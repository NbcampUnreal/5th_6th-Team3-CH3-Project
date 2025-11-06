#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSGameOverWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class PROJECTSOUL_API UPSGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void WidgetFadeIn();

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

	UFUNCTION()
	void MainMenuButtonClick();

	UFUNCTION()
	void RestartButtonClick();

	UFUNCTION()
	void MainMenuButtonHovered();

	UFUNCTION()
	void MainMenuButtonUnHovered();

	UFUNCTION()
	void RestartButtonHovered();

	UFUNCTION()
	void RestartButtonUnHovered();

private :
	void UpdateUI();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReStartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MainMenuButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ReStartButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ClearOrDieText;

	FTimerHandle GameOverFadeInTimer;

	float GameOverFadeInTime;
};
