#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PSGameStateBase.generated.h"

UCLASS()
class PROJECTSOUL_API APSGameStateBase : public AGameStateBase
{
    GENERATED_BODY()

public:
    APSGameStateBase();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void AddScore(int32 Amount);
    
    UFUNCTION(BlueprintCallable, Category = "Game")
	void DecreaseEnemyCount();

	int32 GetRemainingEnemies() const;

	void SetRemainingEnemies(int32 Count);

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGamePlaying;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGameOver;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGameClear;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    int32 CurrentScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    int32 RemainingEnemies;
};
