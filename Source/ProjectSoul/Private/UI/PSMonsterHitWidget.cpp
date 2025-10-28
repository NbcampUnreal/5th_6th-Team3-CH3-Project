#include "UI/PSMonsterHitWidget.h"

void UPSMonsterHitWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UPSMonsterHitWidget::ShowHitWidget(AActor* Monster)
{
	UE_LOG(LogTemp, Warning, TEXT("ShowHitWidget"));
}
