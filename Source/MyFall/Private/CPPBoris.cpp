// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBoris.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACPPBoris::ACPPBoris()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPPBoris::BeginPlay()
{
	Super::BeginPlay();

	// Rotate camera to look at face side
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetControlRotation(FRotator(-20, GetActorRotation().Yaw + 180, 0));
}

void ACPPBoris::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSliding)
	{
		auto ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, 1.0f, false);
	}
}

void ACPPBoris::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPPBoris::Move(float XValue, float YValue)
{
	if (CanMove)
	{
		auto ControlRotation = GetControlRotation();
		auto HorizontalInput = UKismetMathLibrary::GetRightVector(FRotator(0, ControlRotation.Yaw, ControlRotation.Roll));
		auto VerticalInput = UKismetMathLibrary::GetForwardVector(FRotator(0, ControlRotation.Yaw, 0));
		AddMovementInput(HorizontalInput, XValue);
		AddMovementInput(VerticalInput, YValue);
		// Swing on a rope
		if (IsValid(RopePartRef))
		{
			RopePartRef->AddImpulse(VerticalInput * 500 * YValue, NAME_None, false);
		}
	}
}

