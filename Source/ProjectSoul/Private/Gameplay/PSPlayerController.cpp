#include "Gameplay/PSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "UI/PSUIManagerSubsystem.h"

APSPlayerController::APSPlayerController()
{

}

void APSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	PlayerCameraManager->ViewPitchMin = -70.f;
	PlayerCameraManager->ViewPitchMax = 60.f;


	GetGameInstance()->GetSubsystem<UPSUIManagerSubsystem>()->ShowCurrentWidget();
}
