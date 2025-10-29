#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSHealingPotion.generated.h"

UCLASS()
class PROJECTSOUL_API APSHealingPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSHealingPotion();

	UFUNCTION(BlueprintCallable, Category = "Item|Healing")
	void UseItem(AActor* TargetActor);

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item|Healing")
	float HealAmount;

};
