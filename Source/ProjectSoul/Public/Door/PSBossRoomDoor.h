#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSBossRoomDoor.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTSOUL_API APSBossRoomDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	APSBossRoomDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void SetLocked(bool bLocked);

	UFUNCTION(BlueprintPure, Category = "Door")
	bool GetLocked()const;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	TObjectPtr<UStaticMeshComponent> LeftDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	TObjectPtr<UStaticMeshComponent> RightDoor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	TObjectPtr<UBoxComponent> DoorBlocker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Effects")
	TObjectPtr<USoundBase> DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Effects")
	TObjectPtr<USoundBase> DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	FRotator LeftOpenRot;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Door")
	FRotator RightOpenRot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool bIsLocked;

	FRotator LeftClosedRot;
	FRotator RightClosedRot;
};
