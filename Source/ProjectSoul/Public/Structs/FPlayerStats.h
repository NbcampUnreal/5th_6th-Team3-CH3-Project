#pragma once

#include "CoreMinimal.h"
#include "Structs/FStat.h"
#include "FPlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
    GENERATED_BODY()

public:
    FPlayerStats();

    void RestoreAll();

    float GetHealthPercent() const;

    float GetManaPercent() const;

    float GetStaminaPercent() const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStat Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStat Mana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStat Stamina;
};