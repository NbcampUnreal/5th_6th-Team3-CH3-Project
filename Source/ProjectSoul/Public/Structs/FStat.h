#pragma once

#include "CoreMinimal.h"
#include "FStat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
    GENERATED_BODY()

public:
    FStat();

    float GetCurrent() const;

    float GetMax() const;

    void SetCurrent(float NewValue);

    void SetMax(float NewMax);

    void AdjustValue(float Delta);

    void RestoreFull();

    bool IsZero() const;

    float GetPercent() const;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
    float MaxValue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
    float CurrentValue;
};
