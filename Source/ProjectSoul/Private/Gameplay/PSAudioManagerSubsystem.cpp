#include "Gameplay/PSAudioManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

UPSAudioManagerSubsystem::UPSAudioManagerSubsystem() :
	CurrentBGMComponent(nullptr)
{
	ConstructorHelpers::FObjectFinder<USoundBase> DefaultBGMObj(TEXT("/Game/Resources/Sounds/Background/CavesAndDungeons/CUE/The_Labyrinth_Loop_B_Cue.The_Labyrinth_Loop_B_Cue"));
	if (DefaultBGMObj.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("DefaultBGMObj Loaded Successfully"));
		DefaultBGM = DefaultBGMObj.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> BossBGMObj(TEXT("/Game/Resources/Sounds/Background/Starter_Pack_v_2_0/Cues/The_Adventurer_Preparing_Full_Cue.The_Adventurer_Preparing_Full_Cue"));
	if (BossBGMObj.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("BossBGMObj Loaded Successfully"));
		BossBGM = BossBGMObj.Object;
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
	if (DefaultBGM)
	{
		BGMMap.Add("Default", DefaultBGM);
	}

	if (BossBGM)
	{
		BGMMap.Add("Boss", BossBGM);
	}
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

void UPSAudioManagerSubsystem::PlayBGM(FName BGMKey, float FadeInTime)
{
	if (!BGMMap.Contains(BGMKey))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayBGM: '%s' key not found"), *BGMKey.ToString());
		return;
	}

	if (CurrentBGMComponent && CurrentBGMComponent->IsPlaying())
	{
		CurrentBGMComponent->FadeOut(FadeInTime, 0.0f);
	}

	CurrentBGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(), BGMMap[BGMKey], 1.0f, 1.0f, 0.0f, nullptr, true);
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
