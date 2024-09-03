// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBoris.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputAction.h"
#include "SoundtrackManager.h"

ACPPBoris::ACPPBoris()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPPBoris::BeginPlay()
{
	Super::BeginPlay();

	EnableMovement();

	// Rotate camera to look at face side
	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetControlRotation(FRotator(-20, GetActorRotation().Yaw + 180, 0));

	// Setup input
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ACPPBoris::HandleMove);
	}
	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Started, this, &ACPPBoris::HandleJump);
	}
	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ACPPBoris::HandleLook);
	}
	if (ActionInteract)
	{
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &ACPPBoris::HandleInteraction);
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Completed, this, &ACPPBoris::OnInteractionStopped);
	}
	if (ActionGrab)
	{

	}
}

void ACPPBoris::StopHiding_Implementation()
{

}

void ACPPBoris::HandleSpecialJumpAbility()
{
	// Trace capsule to check if threre's climb or wall jump ledge in front of player
	FHitResult OutHitResult;
	CapsuleTrace(OutHitResult);

	// If there's a ledge, perform special ability
	if (IsValid(OutHitResult.GetActor()))
	{
		// Tag of BP_WallJumpLedge
		if (OutHitResult.GetActor()->ActorHasTag("WallJump"))
		{
			if (JumpMaxCount == 1)
			{
				UGameplayStatics::PlaySound2D(this, JumpShout);
			}

			JumpMaxCount = 2;
			return;
		}

		// Tag of BP_ClimbLedge
		if (OutHitResult.GetActor()->ActorHasTag("Climb"))
		{
			TryToClimb(OutHitResult);
		}
	}
	JumpMaxCount = 1;
}

void ACPPBoris::HandleInteraction()
{
	if (CanInteract)
	{
		StopGrabbing();

		switch (AvailableInteractible)
		{
		case EInteractibleTypes::Trap:
			if (IsSettingTrap == false)
			{
				StartSettingTrap();
			}
			break;

		case EInteractibleTypes::Hideout:
			if (IsHiding == false)
			{
				Hide();
			}
			break;

		case EInteractibleTypes::DunkEasterEgg:
			AvailableInteractible = EInteractibleTypes::None;
			PerformDunkEasterEgg();
			break;
		}
	}
}

void ACPPBoris::OnInteractionSucceded()
{
	Interact.Broadcast();
	OnInteractionStopped();
}

void ACPPBoris::OnInteractionStopped()
{
	if (IsSettingTrap)
	{
		IsSettingTrap = false;
		CanMove = true;
		StoppedInteraction.Broadcast();
		if (SetTrapAnimMontage)
		{
			StopAnimMontage(SetTrapAnimMontage);
		}
	}
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

void ACPPBoris::HandleMove(const FInputActionValue& Value)
{
	if (CanMove)
	{
		FRotator ControlRotation = GetControlRotation();
		FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, ControlRotation.Yaw, ControlRotation.Roll));
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, ControlRotation.Yaw, 0));
		FVector2D MovementInputVector = Value.Get<FVector2D>();

		AddMovementInput(RightVector, MovementInputVector.X);
		AddMovementInput(ForwardVector, MovementInputVector.Y);
		// Swing on a rope
		if (IsValid(RopePartRef))
		{
			RopePartRef->AddImpulse(ForwardVector * 500 * MovementInputVector.Y, NAME_None, false);
		}
	}
}

void ACPPBoris::HandleJump()
{
	if (CanMove)
	{
		HandleSpecialJumpAbility();

		Jump();
		IsJumping = true;
	}
	else
	{
		StopHiding();
	}
}

void ACPPBoris::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	IsJumping = false;
}

void ACPPBoris::HandleLook(const FInputActionValue& Value)
{
	FVector2D LookInputVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookInputVector.X * Sensitivity);

	float PitchValue = LookInputVector.Y * Sensitivity;
	if (GrabbedObjectIsClipping)
	{
		PitchValue = FMath::Clamp(PitchValue, -1, 0);
	}
	AddControllerPitchInput(PitchValue);
}

void ACPPBoris::CapsuleTrace(FHitResult& OutHit)
{
	FVector CapsuleCenter = GetActorLocation() + GetActorForwardVector() * 40.f + FVector(0, 0, -20);
	TArray<AActor*> IgnoreActors;

	UKismetSystemLibrary::CapsuleTraceSingle(
		this,
		CapsuleCenter,
		CapsuleCenter,
		20.f,
		55.f,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		OutHit,
		true
	);
}

void ACPPBoris::StartSettingTrap()
{
	AvailableInteractible = EInteractibleTypes::None;
	IsSettingTrap = true;
	CanMove = false;
	float AnimationTime = PlayAnimMontage(SetTrapAnimMontage, 1);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACPPBoris::OnInteractionSucceded, AnimationTime, false);
}

void ACPPBoris::Hide()
{
	AvailableInteractible = EInteractibleTypes::None;
	IsHiding = true;
	CanMove = false;
	CanGrab = false;
	
	// Lower the music
	ASoundtrackManager* SoundtrackManager = 
		Cast<ASoundtrackManager>(UGameplayStatics::GetActorOfClass(
			this, ASoundtrackManager::StaticClass()));
	if (SoundtrackManager)
	{
		SoundtrackManager->LowPitch();
	}

	PlayHidingAnim();
}

void ACPPBoris::EnableMovement()
{
	CanMove = true;
	CanGrab = true;
	CanInteract = true;
}

void ACPPBoris::DisableMovement()
{
	CanMove = false;
	CanGrab = false;
	CanInteract = false;
}

