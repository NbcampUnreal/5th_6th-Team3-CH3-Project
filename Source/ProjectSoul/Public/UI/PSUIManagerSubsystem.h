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

private:
	void SetCurrentWidget();

	void ShowMainMenuUI();

	void ShowPlayerHUD();

	void ShowGameOverUI();


public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	UUserWidget* PlayerHUDWidgetInstance;

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

	/*UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	UUserWidget* PlayerHUDWidgetInstance;*/

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY()
	UUserWidget* GameOverWidgetInstance;

	
};
