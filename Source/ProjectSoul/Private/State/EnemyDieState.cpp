#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyDieState::OnEnter()
{
    Super::OnEnter();
    UE_LOG(LogTemp, Warning, TEXT("Enemy : Die state."));
    APSEnemy* Enemy = Cast<APSEnemy>(GetEnemyCharacter());//inefficiency
    if (!Enemy) return;
    Enemy->SetIsDead(true);

    AAIController* AIController = Cast<AAIController>(Enemy->GetController());
    if (AIController)
        AIController->StopMovement();

    Enemy->GetCharacterMovement()->DisableMovement();

    USkeletalMeshComponent* Mesh = Enemy->GetMesh();
    if (Mesh)
    {
        Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
        Mesh->SetSimulatePhysics(true);
        Mesh->WakeAllRigidBodies();
        Mesh->SetAllBodiesBelowSimulatePhysics(TEXT("pelvis"), true);
        Mesh->bBlendPhysics = true;
    }

    Enemy->GetWorldTimerManager().SetTimer(
        DestroyTimerHandle,
        [Enemy]()
        {
            if (IsValid(Enemy))
            {
                Enemy->Destroy();
            }
        },
        3.0f,
        false
    );
}

void UEnemyDieState::OnExit()
{
    Super::OnExit();
}

