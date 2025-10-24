#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMonsterWidget.generated.h"

class UProgressBar;
class UWidgetComponent;
class APSEnemy;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPSMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void UpdateMonsterHP(float Percent);

	void ShowMonsterHP();
	void HiddenMonsterHP();
	void ShowHitMonsterHP();
	void HiddenHitMonsterHP();

private:
	APSCharacter* GetCharacter();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;
	FTimerHandle ShowMonsterHPTimer;
	bool bLockOn;

	float TestHP;
};
