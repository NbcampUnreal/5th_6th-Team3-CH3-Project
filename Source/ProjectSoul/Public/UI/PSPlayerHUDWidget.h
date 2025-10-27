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
	void ShowLockOn(AActor* LockOnMonster);

	void HiddenLockOn();

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnUpdateHPBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void OnUpdateMPBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void OnUpdateStaminaBar(float CurrentValue, float MaxValue);

	void UpdateLockOnPosition();

	APSCharacter* GetCharacter();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> HPBarContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> MPBarContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> StaminaBarContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> MPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LockOnImage;

	FTimerHandle LockOnPositionHandle;
	AActor* LockOnTarget;

	float SizeBoxMultiplier;
};
