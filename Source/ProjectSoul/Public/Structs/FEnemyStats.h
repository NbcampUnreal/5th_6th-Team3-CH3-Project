#pragma once

#include "CoreMinimal.h"
#include "Structs/FStat.h"
#include "FEnemyStats.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats
{
    GENERATED_BODY()

public:
    FEnemyStats();

    void RestoreAll();

    float GetHealthPercent() const;

    float GetStaminaPercent() const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStat Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStat Stamina;
};
