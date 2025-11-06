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

private:
	UFUNCTION()
	void StartButtonClick();

	UFUNCTION()
	void EndButtonClick();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EndButton;
};
