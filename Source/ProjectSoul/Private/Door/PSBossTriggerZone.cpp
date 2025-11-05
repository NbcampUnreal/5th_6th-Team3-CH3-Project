#include "Door/PSBossTriggerZone.h"
#include "Components/BoxComponent.h"
#include "Door/PSBossRoomDoor.h"
#include "Enemy/PSBossEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Character/PSCharacter.h"
#include "Gameplay/PSAudioManagerSubsystem.h"
#include "Gameplay/PSGameModeBase.h"
#include "Kismet/GameplayStatics.h"

APSBossTriggerZone::APSBossTriggerZone()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	if (TriggerBox)
	{
		SetRootComponent(TriggerBox);
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APSBossTriggerZone::OnPlayerEnter);
	}

	bBossDefeated = false;
}

void APSBossTriggerZone::BeginPlay()
{
	Super::BeginPlay();

	if (BossActor)
	{
		APSBossEnemy* Boss = Cast<APSBossEnemy>(BossActor);
		if (Boss)
		{
			Boss->OnBossDefeated.AddDynamic(this, &APSBossTriggerZone::OnBossDefeated);
		}
	}

	if (APSGameModeBase* GameMode = Cast<APSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->OnAllEnemiesDead.AddDynamic(this, &APSBossTriggerZone::OpenDoor);
	}
}

void APSBossTriggerZone::OnPlayerEnter(
	UPrimitiveComponent* OverlappingComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, const
	FHitResult& SweepResult
)
{
	if (APSCharacter* Player = Cast<APSCharacter>(OtherActor))
	{
		if (BossDoor && !bBossDefeated)
		{
			BossDoor->CloseDoor();
			BossDoor->SetLocked(true);

			if (UPSAudioManagerSubsystem* Audio = GetGameInstance()->GetSubsystem<UPSAudioManagerSubsystem>())
			{
				Audio->PlayBGM("Boss", 0.4f);
			}

			TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		if (BossClass && BossSpawnPoint)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			APSBossEnemy* SpawnedBoss = GetWorld()->SpawnActor<APSBossEnemy>(
				BossClass,
				BossSpawnPoint->GetActorLocation(),
				BossSpawnPoint->GetActorRotation(),
				SpawnParams
			);

			if (SpawnedBoss)
			{
				UE_LOG(LogTemp, Warning, TEXT("Boss spawned and playing summon animation."));
				SpawnedBoss->SetActorEnableCollision(false);
				if (AAIController* AI = Cast<AAIController>(SpawnedBoss->GetController()))
				{
					if (AI->GetBrainComponent())
					{
						AI->GetBrainComponent()->StopLogic(TEXT("Waiting for summon animation"));
					}
				}

				UAnimInstance* Anim = SpawnedBoss->GetMesh()->GetAnimInstance();
				if (Anim && SpawnedBoss->SpawnMontage)
				{
					float Duration = Anim->Montage_Play(SpawnedBoss->SpawnMontage);

					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(
						TimerHandle,
						[SpawnedBoss]()
						{
							UE_LOG(LogTemp, Warning, TEXT("Boss summon animation ended ¡æ activating boss."));
							SpawnedBoss->SetActorEnableCollision(true);
							if (AAIController* AI = Cast<AAIController>(SpawnedBoss->GetController()))
							{
								if (AI->GetBrainComponent())
								{
									AI->GetBrainComponent()->StartLogic();
								}
							}
						},
						Duration,
						false
					);
				}
				else
				{
					SpawnedBoss->SetActorEnableCollision(true);
					if (AAIController* AI = Cast<AAIController>(SpawnedBoss->GetController()))
					{
						if (AI->GetBrainComponent())
						{
							AI->GetBrainComponent()->StartLogic();
						}
					}
				}
			}
		}
	}
}

void APSBossTriggerZone::OnBossDefeated()
{
	if (BossDoor)
	{
		OpenDoor();
		bBossDefeated = true;
	}
}

void APSBossTriggerZone::OpenDoor()
{
	BossDoor->SetLocked(false);
	BossDoor->OpenDoor();
}