#include "UI/PSLoadingWidget.h"

void UPSLoadingWidget::NativePreConstruct()
{
	UFunction* LoadingAnim = FindFunction(FName("LoadingAnim"));
	if (LoadingAnim)
	{
		ProcessEvent(LoadingAnim, nullptr);
	}
}
