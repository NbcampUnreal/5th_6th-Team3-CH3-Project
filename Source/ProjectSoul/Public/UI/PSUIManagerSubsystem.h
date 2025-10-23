#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PSUIManagerSubsystem.generated.h"

UCLASS()
class PROJECTSOUL_API UPSUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPSUIManagerSubsystem();

	void ShowCurrentWidget();
	void HideCurrentWidget();

	void HUDUpdate();


private:
	void SetCurrentWidget();

	

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "MainMenuWidget")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	UUserWidget* PlayerHUDWidgetInstance;


	TSubclassOf<UUserWidget> CurrentWidgetClass;
	UUserWidget* CurrentWidgetInstance;
};
