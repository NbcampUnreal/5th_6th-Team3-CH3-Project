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

	UFUNCTION()
	void ShowCurrentWidget(bool bIsGameOver);

	void LevelLoading(FName LevelName);
	

private:
	UFUNCTION()
	void OpenLevel();

	void ShowMainMenuUI();

	void ShowPlayerHUD();

	void ShowGameOverUI();

	void ShowLoadingUI();


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

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	UPROPERTY()
	UUserWidget* LoadingWidgetInstance;

	FName OpenLevelName;
};
