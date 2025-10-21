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
	
public:

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void StartButtonClick();
	UFUNCTION()
	void EndButtonClick();

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* EndButton;

};
