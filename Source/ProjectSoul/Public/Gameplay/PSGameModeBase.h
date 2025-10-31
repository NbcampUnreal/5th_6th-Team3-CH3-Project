#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, IsClear);

UCLASS()
class PROJECTSOUL_API APSGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    APSGameModeBase();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void StartGame();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void EndGame(bool bIsClear);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void RestartGame();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void AddPlayerScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void OnEnemyKilled(int32 EnemyScore);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void OnPlayerKilled();

protected:
    virtual void BeginPlay() override;


public:
    UPROPERTY(BlueprintAssignable)
    FOnGameOver OnGameOver;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Game")
    bool bIsGamePlaying;

    UPROPERTY(VisibleAnywhere, Category = "Game")
    bool bIsGameOver;

    UPROPERTY(VisibleAnywhere, Category = "Game")
    int32 RemainingEnemies;

    void CheckClearCondition();

    UPROPERTY(EditAnywhere, Category = "Game")
    float RestartDelay = 3.0f;
};
