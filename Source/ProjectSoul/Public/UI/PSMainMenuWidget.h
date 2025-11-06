#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMainMenuWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class PROJECTSOUL_API UPSMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void StartButtonClick();

	UFUNCTION()
	void EndButtonClick();

	UFUNCTION()
	void StartButtonHovered();

	UFUNCTION()
	void StartButtonUnHovered();

	UFUNCTION()
	void EndButtonHovered();

	UFUNCTION()
	void EndButtonUnHovered();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EndButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StartButtonText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> EndButtonText;
};
