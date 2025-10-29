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
	void UpdateUI();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

protected:
	UFUNCTION()
	void MainMenuButtonClick();

	UFUNCTION()
	void RestartButtonClick();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ReStartButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalScoreText;

	UPROPERTY(meta = (BindWidget))

	UTextBlock* ClearOrDieText;
};
