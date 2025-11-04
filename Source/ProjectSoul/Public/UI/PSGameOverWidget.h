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
	TObjectPtr<UButton> MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ReStartButton;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalScoreText;

	UPROPERTY(meta = (BindWidget))

	TObjectPtr<UTextBlock> ClearOrDieText;

	FTimerHandle GameOverFadeInTimer;

	float GameOverFadeInTime;
};
