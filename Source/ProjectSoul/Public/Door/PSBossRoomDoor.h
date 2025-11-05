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
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	UStaticMeshComponent* RightDoor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component")
	UBoxComponent* DoorBlocker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Effects")
	USoundBase* DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door|Effects")
	USoundBase* DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	FRotator LeftOpenRot;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Door")
	FRotator RightOpenRot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	bool bIsLocked;

	FRotator LeftClosedRot;
	FRotator RightClosedRot;

	
};
