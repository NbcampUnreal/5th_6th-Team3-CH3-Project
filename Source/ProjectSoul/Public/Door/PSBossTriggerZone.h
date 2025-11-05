#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSBossTriggerZone.generated.h"

class UBoxComponent;
class APSBossRoomDoor;
class APSBossEnemy;

UCLASS()
class PROJECTSOUL_API APSBossTriggerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	APSBossTriggerZone();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerEnter(
		UPrimitiveComponent* OverlappingComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnBossDefeated();

	UFUNCTION()
	void OpenDoor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BossRoom|Component")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossRoom")
	APSBossRoomDoor* BossDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossRoom")
	AActor* BossActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossRoom")
	bool bBossDefeated;
	
	UPROPERTY(EditAnywhere, Category = "Boss")
	TSubclassOf<APSBossEnemy> BossClass;

	UPROPERTY(EditAnywhere, Category = "Boss")
	AActor* BossSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Boss")
	UAnimMontage* BossSpawnMontage; 

	FTimerHandle BossSpawnTimerHandle;

	void SpawnBossAfterMontage();

};
