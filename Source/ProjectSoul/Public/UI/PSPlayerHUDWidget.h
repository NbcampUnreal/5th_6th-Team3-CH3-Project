#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSPlayerHUDWidget.generated.h"

class USizeBox;
class UProgressBar;
class UImage;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateUI();
	

private:
	virtual void NativeOnInitialized() override;

	void SetHPPersent(float Amount);
	void SetMPPersent(float Amount);
	void SetStaminaPersent(float Amount);
	void SetHPBarSize(int Amount);
	void SetMPBarSize(int Amount);
	void SetStaminaBarSize(int Amount);


	void ShowLockOn();
	void HiddenLockOn();
	void UpdateLockOnPosition();


	APSCharacter* GetCharacter();

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* HPBarContainer;
	UPROPERTY(meta = (BindWidget))
	USizeBox* MPBarContainer;
	UPROPERTY(meta = (BindWidget))
	USizeBox* StaminaBarContainer;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* MPBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;


	UPROPERTY(meta = (BindWidget))
	UImage* LockOnImage;



	//test
	UPROPERTY(EditAnywhere, Category = "Test Value")
	float HPBarValue;
	UPROPERTY(EditAnywhere, Category = "Test Value")
	float MPBarValue;
	UPROPERTY(EditAnywhere, Category = "Test Value")
	float StaminaValue;

	UPROPERTY(EditAnywhere, Category = "Test Value")
	float HPBarContainerXSize;
	UPROPERTY(EditAnywhere, Category = "Test Value")
	float MPBarContainerXSize;
	UPROPERTY(EditAnywhere, Category = "Test Value")
	float StaminaBarContainerXSize;

	
	FTimerHandle LockOnPositionHandle;
};
