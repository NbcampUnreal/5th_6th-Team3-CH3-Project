#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMonsterWidget.generated.h"

class UProgressBar;

UCLASS()
class PROJECTSOUL_API UPSMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateMonsterHP(float Percent);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;
};
