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

private :
	void UpdateUI();


public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ReStartButton;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClearOrDieText;

	FTimerHandle GameOverFadeInTimer;

	float GameOverFadeInTime;
};
