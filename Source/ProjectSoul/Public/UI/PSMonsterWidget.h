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
	void UpdateMonsterHP(float Percent);

	void ShowTargetMonsterHP();
	void HiddenTargetMonsterHP();
	void ShowHitMonsterHP();
	void HiddenHitMonsterHP();

private:
	virtual void NativeOnInitialized() override;
	APSCharacter* GetCharacter();

private:
	UProgressBar* HPBar;
	FTimerHandle ShowMonsterHPTimer;
	bool bLockOn;

	float TestHP;
};
