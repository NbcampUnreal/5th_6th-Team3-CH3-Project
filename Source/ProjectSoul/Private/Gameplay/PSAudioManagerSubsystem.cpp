#include "Gameplay/PSAudioManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

UPSAudioManagerSubsystem::UPSAudioManagerSubsystem() :
	CurrentBGMComponent(nullptr)
{
	ConstructorHelpers::FObjectFinder<USoundBase> BGMObj(TEXT("/Game/Resources/Sounds/Background/CavesAndDungeons/CUE/The_Labyrinth_Loop_B_Cue.The_Labyrinth_Loop_B_Cue"));
	if (BGMObj.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("BGM Loaded Successfully"));
		DefaultBGM = BGMObj.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenObj(TEXT("/Game/Audio/SA_Default.SA_Default"));
	if (AttenObj.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Sound Attenuation Loaded Successfully"));
		DefaultAttenuation = AttenObj.Object;
	}
}

void UPSAudioManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UPSAudioManagerSubsystem::PlaySFX(USoundBase* Sound, FVector Location, float Volume)
{
	if (!Sound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		Sound,
		Location,
		Volume,
		1.0f,
		0.0f,
		DefaultAttenuation ? DefaultAttenuation : nullptr
	);
}

void UPSAudioManagerSubsystem::PlayBGM(float FadeInTime)
{
	if (!DefaultBGM)
	{
		return;
	}

	if (CurrentBGMComponent && CurrentBGMComponent->IsPlaying())
	{
		CurrentBGMComponent->FadeOut(FadeInTime, 0.0f);
	}

	CurrentBGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DefaultBGM, 1.0f, 1.0f, 0.0f, nullptr, true);
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
