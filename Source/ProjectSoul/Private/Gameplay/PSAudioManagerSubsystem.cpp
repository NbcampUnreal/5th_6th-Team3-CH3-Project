#include "Gameplay/PSAudioManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

UPSAudioManagerSubsystem::UPSAudioManagerSubsystem() :
	CurrentBGMComponent(nullptr)
{
}

void UPSAudioManagerSubsystem::PlaySFX(USoundBase* Sound, FVector Location, float Volume)
{
	if (!Sound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, Volume);
}

void UPSAudioManagerSubsystem::PlayBGM(USoundBase* Sound, float FadeInTime)
{
	if (!Sound)
	{
		return;
	}

	if (CurrentBGMComponent && CurrentBGMComponent->IsPlaying())
	{
		CurrentBGMComponent->FadeOut(FadeInTime, 0.0f);
	}

	CurrentBGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(), Sound, 1.0f, 1.0f, 0.0f, nullptr, true);
	if (CurrentBGMComponent)
	{
		CurrentBGMComponent->FadeIn(FadeInTime, 1.0f);
	}
}

void UPSAudioManagerSubsystem::StopBGM(float FadeOutTime)
{
	if (CurrentBGMComponent && CurrentBGMComponent->IsPlaying())
	{
		CurrentBGMComponent->FadeOut(FadeOutTime, 0.0f);
	}
}
