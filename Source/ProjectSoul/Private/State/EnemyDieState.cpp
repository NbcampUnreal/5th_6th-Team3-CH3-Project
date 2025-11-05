#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Die state."));
    APSEnemy* Enemy = Cast<APSEnemy>(GetEnemyCharacter());
    if (!Enemy) return;
    Enemy->SetIsDead(true);

    AAIController* AIController = Cast<AAIController>(Enemy->GetController());
    if (AIController)
        AIController->StopMovement();

    UAnimInstance* Anim = Enemy->GetMesh()->GetAnimInstance();
    Anim->StopAllMontages(0.1f);

    UWorld* World = Enemy->GetWorld();
    if (World)
    {
        World->GetTimerManager().SetTimer(
            RagdollTimer,
            [World, Enemy]()
            {
                if (IsValid(Enemy))
                {
                    Enemy->GetCharacterMovement()->DisableMovement();

                    if (UCapsuleComponent* Capsule = Enemy->GetCapsuleComponent())
                    {
                        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                    }

                    if (USkeletalMeshComponent* Mesh = Enemy->GetMesh())
                    {
                        Mesh->SetSimulatePhysics(true);
                        Mesh->SetAllBodiesBelowSimulatePhysics(TEXT("pelvis"), true);
                        Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
                    }

                    UE_LOG(LogTemp, Warning, TEXT(" Ragdoll Activated"));
                }
                if (IsValid(World) && IsValid(Enemy))
                {
                    World->GetTimerManager().SetTimerForNextTick([Enemy]()
                        {
                            Enemy->SetLifeSpan(3.0f);
                        });
                }
            },
            0.5f,
            false
        );
    }
}

void UEnemyDieState::OnExit()
{
    Super::OnExit();
}

