#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PSAudioManagerSubsystem.generated.h"

class USoundBase;
class UAudioComponent;

UCLASS(Blueprintable)
class PROJECTSOUL_API UPSAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPSAudioManagerSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    void PlaySFX(USoundBase* Sound, FVector Location, float Volume = 1.0f);

    void PlaySFX2D(USoundBase* Sound, float Volume = 1.0f);

    void PlayBGM(FName BGMKey, float FadeInTime = 1.f);

    void StopBGM(float FadeOutTime = 1.0f);

	void PlayGameOverSFX(float Volume = 1.0f);

	void PlayGameClearSFX(float Volume = 1.0f);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> DefaultBGM;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> BossBGM;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> GameOverSFX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> GameClearSFX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundAttenuation> DefaultAttenuation;

private:
    UPROPERTY()
    TObjectPtr<UAudioComponent> CurrentBGMComponent;

    UPROPERTY()
    TMap<FName, USoundBase*> BGMMap;
};
