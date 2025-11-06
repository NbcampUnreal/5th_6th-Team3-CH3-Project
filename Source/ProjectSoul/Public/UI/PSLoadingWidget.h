#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSLoadingWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class PROJECTSOUL_API UPSLoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
};
