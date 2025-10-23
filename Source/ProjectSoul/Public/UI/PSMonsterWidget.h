#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMonsterWidget.generated.h"

class UProgressBar;
class UWidgetComponent;
class APSEnemy;

UCLASS()
class PROJECTSOUL_API UPSMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMonsterHP(UWidgetComponent* OverheadWidget, APSEnemy* Monster);

private:
	virtual void NativeOnInitialized() override;


private:
	UProgressBar* HPBar;
};
