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
	void UpdateMonsterHP();

	void ShowMonsterHP();
	void HiddenMonsterHP();

	void SetMonsterHP(UWidgetComponent* OverheadWidget, APSEnemy* Monster);

private:
	virtual void NativeOnInitialized() override;

	APSCharacter* GetCharacter();

private:
	UProgressBar* HPBar;
	
};
