#include "State/EnemyDieState.h"
#include "Enemy/PSEnemy.h"
#include "Enemy/PSEnemyAIController.h"
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

    Enemy->GetWorldTimerManager().SetTimer(
        RagdollTimer,
        [Enemy]()
        {
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

            UE_LOG(LogTemp, Warning, TEXT("Ragdoll Activated!"));
        },
        0.8f,
        false 
    );

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

