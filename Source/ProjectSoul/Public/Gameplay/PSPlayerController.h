#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PSPlayerController.generated.h"

UCLASS()
class PROJECTSOUL_API APSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APSPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	void ShowMainMenu();

public:
	UPROPERTY(EditAnywhere, Category = "MainMenuWidget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = "MainMenuWidget")
	UUserWidget* MainMenuWidgetInstance;
};
