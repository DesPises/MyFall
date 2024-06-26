// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPPBoris.generated.h"

UCLASS()
class MYFALL_API ACPPBoris : public ACharacter
{
	GENERATED_BODY()

public:
	ACPPBoris();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	float GrabSocketZDefault;

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

};
