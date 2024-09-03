// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Interaction.h"
#include "CPPBoris.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStoppedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnHideDelegate);

UENUM(BlueprintType)
enum class EInteractibleTypes : uint8
{
	None			UMETA(DisplayName = "None"),
	Trap			UMETA(DisplayName = "Trap"),
	Hideout			UMETA(DisplayName = "Hideout"),
	DunkEasterEgg	UMETA(DisplayName = "DunkEasterEgg"),
};

UCLASS()
class MYFALL_API ACPPBoris : public ACharacter, public IInteraction
{
	GENERATED_BODY()

public:
	ACPPBoris();

	// Delegate for animation blueprint to stop "setting trap" sounds
	UPROPERTY(BlueprintAssignable)
	FOnInteractionStoppedDelegate StoppedInteraction;

	// Delegate for interaction with trap
	UPROPERTY(BlueprintAssignable)
	FOnInteractionStoppedDelegate Interact;

	// Delegate for interaction with trap
	UPROPERTY(BlueprintAssignable)
	FOnHideDelegate HideD;

	// Delegate for interaction with trap
	UPROPERTY(BlueprintAssignable)
	FOnUnHideDelegate UnhideD;

protected:
	virtual void BeginPlay() override;

	// Gameplay mechanics

	UFUNCTION(BlueprintNativeEvent)
	void StopHiding();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayHidingAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void TryToClimb(const FHitResult& OutHit);
	
	void HandleSpecialJumpAbility();

	// Interaction
	void HandleInteraction();
	void OnInteractionSucceded();
	void OnInteractionStopped();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopGrabbing();

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SetTrapAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	USoundBase* JumpShout = nullptr;

public:
	virtual void Tick(float DeltaTime) override;

	// Input

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ActionInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ActionGrab = nullptr;

	UFUNCTION()
	void HandleMove(const FInputActionValue& Value);

	UFUNCTION()
	void HandleJump();

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	void HandleLook(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EnableMovement();

	UFUNCTION(BlueprintCallable)
	void DisableMovement();

	// Variables

	// States
	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsSliding;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsHiding;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsClimbing;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsRopeRiding;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsSettingTrap;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsRagdoll;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsGrabbing;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsJumping;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool HandsTied;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool SpeedBoostActive;

	UPROPERTY(BlueprintReadWrite, Category = "States")
	bool IsInvulnerable;

	// Can do
	UPROPERTY(BlueprintReadWrite, Category = "Can do")
	bool CanMove;

	UPROPERTY(BlueprintReadWrite, Category = "Can do")
	bool CanGrab;

	UPROPERTY(BlueprintReadWrite, Category = "Can do")
	bool CanInteract;

	UPROPERTY(BlueprintReadWrite, Category = "Can do")
	bool CanUnhide;

	// Parameters
	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float Sensitivity = 0.5f;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float Pitch;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float YawOutput;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float HandsPositionWhileWalking;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float DefaultJumpMaxZ;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	float DefaultWalkSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	bool GrabbedObjectIsClipping;

	UPROPERTY(BlueprintReadWrite, Category = "Parameters")
	int HP = 3;

	// Components
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UPrimitiveComponent* RopePartRef;

	UPROPERTY(BlueprintReadWrite)
	EInteractibleTypes AvailableInteractible = EInteractibleTypes::None;

	// Easter egg
	UFUNCTION(BlueprintImplementableEvent)
	void PerformDunkEasterEgg();

private:
	// Input
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	// Capsule trace
	UFUNCTION()
	void CapsuleTrace(FHitResult& OutHit);

	// Setting trap
	void StartSettingTrap();

	// Hiding
	void Hide();
};
