#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMonsterHitWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class PROJECTSOUL_API UPSMonsterHitWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowHitWidget(AActor* Monster);

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;

	UPROPERTY(meta = (BindWidget))
	UImage* HitMarkerImage;
};
