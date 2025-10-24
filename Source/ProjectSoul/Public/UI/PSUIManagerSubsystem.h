#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PSUIManagerSubsystem.generated.h"

class UPSPlayerHUDWidget;

UCLASS()
class PROJECTSOUL_API UPSUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPSUIManagerSubsystem();

	void ShowCurrentWidget();
	void HideCurrentWidget();

	void ShowLockOn(AActor* LockOnMonster);
	void HiddenLockOn();

	void ShowMainMenuUI();
	void ShowPlayerHUD();
	void ShowGameOverUI();


private:
	void SetCurrentWidget();

	

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	UUserWidget* PlayerHUDWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY()
	UUserWidget* GameOverWidgetInstance;

	UUserWidget* CurrentWidgetInstance;
};
