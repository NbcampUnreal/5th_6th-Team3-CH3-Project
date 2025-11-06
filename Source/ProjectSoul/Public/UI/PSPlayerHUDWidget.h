#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSPlayerHUDWidget.generated.h"

class USizeBox;
class UProgressBar;
class UImage;
class UTextBlock;
class UVerticalBox;
class UPSQuestTextWidget;
class APSCharacter;

UCLASS()
class PROJECTSOUL_API UPSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void QuestUpdateDelegate(AActor* UnUsed);

	UFUNCTION()
	void QuestUpdate();

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void OnUpdateHPBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void OnUpdateMPBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void OnUpdateStaminaBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void ShowLockOnWidget(AActor* LockOnMonster);

	UFUNCTION()
	void ShowHitWidget(AActor* LockOnMonster, float Damage);

	UFUNCTION()
	void ShowBossStatusWidget(AActor* BossMonster, bool bIsAreaIn);

	UFUNCTION()
	void OnUpdateBossHPBar(AActor* Boss, float Damage);

	UFUNCTION()
	void OnUpdatePotionCount(int32 CurrentPotionCount);

	void HiddenBossStatusWidget();

	void HiddenLockOnWidget();

	void UpdateLockOnPosition();

	APSCharacter* GetCharacter();

	void CreateQuestText(FName QuestName);

	void DeleteQuestText();

public:
	TMap<FName, UPSQuestTextWidget*> QuestMap;

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


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> BossStatsVerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BossName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BossHPBar;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> HPBarBackImageContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> MPBarBackImageContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> StaminaBarBackImageContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PotionImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PotionCountText;

	TSubclassOf<UUserWidget> MonsterHitWidgetClass;

	TSubclassOf<UUserWidget> QuestTextWidgetClass;

	FTimerHandle LockOnPositionHandle;
	AActor* LockOnTarget;

	float SizeBoxMultiplier;
	bool bLockOn;

	float CurrentHP;
	float DisplayHP;
	float LerpSpeed;
	FTimerHandle HPUpdateTimer;

	float CurrentMP;
	float DisplayMP;
	FTimerHandle MPUpdateTimer;
};
