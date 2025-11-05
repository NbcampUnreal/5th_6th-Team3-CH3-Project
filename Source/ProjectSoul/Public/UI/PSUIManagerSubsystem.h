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
	void ShowCurrentWidget();

	void ShowGameOverUI();

	UFUNCTION()
	void ShowLoadingUI();

	void LevelLoading(FName LevelName);

private:
	void ShowMainMenuUI();

	void ShowPlayerHUD();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerHUDWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> GameOverWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> LoadingWidgetInstance;



	FName OpenLevelName;
};
