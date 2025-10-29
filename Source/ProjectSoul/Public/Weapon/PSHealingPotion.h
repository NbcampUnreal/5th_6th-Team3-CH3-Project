#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSHealingPotion.generated.h"

class APSCharacter;

UCLASS()
class PROJECTSOUL_API APSHealingPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APSHealingPotion();

	UFUNCTION(BlueprintCallable, Category = "Item|Healing")
	void UseItem(APSCharacter* Player);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item|Healing")
	float HealAmount;

};
