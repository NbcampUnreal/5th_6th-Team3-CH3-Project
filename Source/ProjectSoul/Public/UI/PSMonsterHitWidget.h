#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSMonsterHitWidget.generated.h"

class UCanvasPanel;
class UTextBlock;
class UImage;

UCLASS()
class PROJECTSOUL_API UPSMonsterHitWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowHitWidget(AActor* Monster, float Damage);

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	
private:
	void SetDamageText(int Damage);
	void UpdateHitPosition();
	void HiddenHitWidget();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> HitCanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> HitMarkerImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageText;

	TObjectPtr<AActor> TargetMonster;

	FTimerHandle HitPositionTimer;
	FTimerHandle HitEndTimer;
	bool bIsAddToViewport;
};
