// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBoris.h"
#include "Kismet/GameplayStatics.h"

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

