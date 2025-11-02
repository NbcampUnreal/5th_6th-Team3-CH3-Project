#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PSAudioManagerSubsystem.generated.h"

class USoundBase;
class UAudioComponent;

UCLASS()
class PROJECTSOUL_API UPSAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPSAudioManagerSubsystem();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlaySFX(USoundBase* Sound, FVector Location, float Volume = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayBGM(USoundBase* Sound, float FadeInTime = 1.f);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopBGM(float FadeOutTime = 1.0f);

private:
    UPROPERTY()
    TObjectPtr<UAudioComponent> CurrentBGMComponent;
};
