#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSQuestTextWidget.generated.h"

class UTextBlock;

UCLASS()
class PROJECTSOUL_API UPSQuestTextWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestText;
};
