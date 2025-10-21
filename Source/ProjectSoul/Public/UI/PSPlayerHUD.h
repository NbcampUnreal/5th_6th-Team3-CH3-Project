#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSPlayerHUD.generated.h"

class USizeBox;
class UProgressBar;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPSPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHPPersent(float Amount);
	void SetMPPersent(float Amount);
	void SetStaminaPersent(float Amount);

	void SetHPBarSize(int Amount);
	void SetMPBarSize(int Amount);
	void SetStaminaBarSize(int Amount);

protected:
	virtual void NativeOnInitialized() override;

private:
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
};
