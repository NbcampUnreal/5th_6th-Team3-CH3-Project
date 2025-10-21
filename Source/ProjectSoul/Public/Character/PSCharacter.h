#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerStateMachine;
class USphereComponent;
struct FInputActionValue;

UCLASS()
class PROJECTSOUL_API APSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	float GetNormalWalkSpeed() const;

	float GetSprintWalkSpeed() const;

	float GetTargetingWalkSpeed() const;

	AActor* GetCurrentTarget() const;

	void SetCurrentTarget(AActor* NewTarget);

	float GetMaxTargetDistance() const;

	void SetIsTargeting(bool Value);

	UFUNCTION(BlueprintPure, Category = "Targeting")
	bool GetIsTargeting() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump(const FInputActionValue& Value);

	UFUNCTION()
	void StopJump(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);

	UFUNCTION()
	void Lock(const FInputActionValue& Value);

	UFUNCTION()
	void Unlock(const FInputActionValue& Value);

private:
	void FindTargetActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<USphereComponent> Scanner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	TObjectPtr<UPlayerStateMachine> StateMachine;

	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TargetingWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float MaxTargetDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	bool bIsTargeting;
};
