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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGamePlaying;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    bool bIsGameOver;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    int32 CurrentScore;

public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    void AddScore(int32 Amount);
};
