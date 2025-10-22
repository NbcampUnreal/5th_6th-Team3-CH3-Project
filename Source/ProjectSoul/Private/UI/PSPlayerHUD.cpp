#include "UI/PSPlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Character/PSCharacter.h"

void UPSPlayerHUD::NativeOnInitialized()
{
	HPBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("HPBarContainer")));
	MPBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("MPBarContainer")));
	StaminaBarContainer = Cast<USizeBox>(GetWidgetFromName(TEXT("StaminaBarContainer")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	
	if (APSCharacter* PSCharacter = GetCharacter())
	{
		SetHPBarSize(500);
		SetMPBarSize(500);
		SetStaminaBarSize(500);
		/*SetHPBarSize(PSCharacter->MaxHP);
		SetMPBarSize(PSCharacter->MaxMP);
		SetStaminaBarSize(PSCharacter->MaxStamina);*/
	}
	
	SetHPPersent(1.0f);
	SetMPPersent(1.0f);
	SetStaminaPersent(1.0f);
}

void UPSPlayerHUD::SetHPPersent(float HPPersent)
{
	HPBar->SetPercent(FMath::Clamp(HPPersent, 0.0f, 1.0f));
}

void UPSPlayerHUD::SetMPPersent(float MPPersent)
{
	MPBar->SetPercent(FMath::Clamp(MPPersent, 0.0f, 1.0f));
}

void UPSPlayerHUD::SetStaminaPersent(float StaminaPersent)
{
	StaminaBar->SetPercent(FMath::Clamp(StaminaPersent, 0.0f, 1.0f));
}

void UPSPlayerHUD::SetHPBarSize(int MaxHP)
{
	HPBarContainer->SetWidthOverride(MaxHP * 2);
	//dfd
}

void UPSPlayerHUD::SetMPBarSize(int MaxMP)
{
	MPBarContainer->SetWidthOverride(MaxMP * 2);
}

void UPSPlayerHUD::SetStaminaBarSize(int MaxStamina)
{
	StaminaBarContainer->SetWidthOverride(MaxStamina * 2);
}

APSCharacter* UPSPlayerHUD::GetCharacter()
{
	if (APlayerController* PlayerContrller = GetWorld()->GetFirstPlayerController())
	{
		if (APSCharacter* PSCharacter = Cast<APSCharacter>(PlayerContrller->GetPawn()))
		{
			return PSCharacter;
		}
	}
	return nullptr;
}


//controller
//UPROPERTY(EditAnywhere, Category = "Widget")
//TSubclassOf<UUserWidget> MainMenuWidgetClass;
//UPROPERTY(EditAnywhere, Category = "Widget")
//TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
//UPROPERTY()
//UUserWidget* MainMenuWidgetInstance;
//UPROPERTY()
//UUserWidget* PlayerHUDWidgetInstance;