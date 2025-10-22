#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameModeBase.generated.h"

UCLASS()
class PROJECTSOUL_API APSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    APSGameModeBase();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void StartGame();
    UFUNCTION(BlueprintCallable, Category = "Game")
    void EndGame();
    UFUNCTION(BlueprintCallable, Category = "Game")
	void RestartGame();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Game State")
    bool bIsGamePlaying;

    UPROPERTY(VisibleAnywhere, Category = "Game State")
    bool bIsGameOver;

    UPROPERTY(EditAnywhere, Category = "Game")
    float RestartDelay = 3.0f;
};

