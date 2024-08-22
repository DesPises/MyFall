// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFallPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <EnhancedInputSubsystems.h>
#include "Blueprint/UserWidget.h"


void AMyFallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
	AsMyFallGameModeBase = Cast<AMyFallGameModeBase>(CurrentGameMode);

	SetInputMappingContext();
}

void AMyFallPlayerController::TriggerLevelTransition()
{
	if (AsMyFallGameModeBase->WaitingForLevelTransition)
	{
		AsMyFallGameModeBase->OpenNextLevel();
	}
}

void AMyFallPlayerController::HandlePause()
{
	if (AsMyFallGameModeBase)
	{
		if (UGameplayStatics::IsGamePaused(this))
		{
			UGameplayStatics::SetGamePaused(this, false);
			AsMyFallGameModeBase->SetInputModeGame();
			DestroyPauseMenuWidgets();
		}
		else
		{
			UGameplayStatics::SetGamePaused(this, true);
			AsMyFallGameModeBase->SetInputModeUI();
			PauseWidget = CreateWidget(this, PauseWidgetClass);
			if (PauseWidget)
			{
				PauseWidget->AddToViewport();
			}
		}
	}
}

void AMyFallPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Handle Level Transition input
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Completed,
			this, &AMyFallPlayerController::TriggerLevelTransition);
	}
	// Handle pause
	if (ActionPause)
	{
		EnhancedInputComponent->BindAction(ActionPause, ETriggerEvent::Started,
			this, &AMyFallPlayerController::HandlePause);
	}
}

void AMyFallPlayerController::SetInputMappingContext()
{
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AMyFallPlayerController::DestroyPauseMenuWidgets()
{
	if (PauseWidget)
	{
		PauseWidget->RemoveFromParent();
	}
	if (SettingsWidget)
	{
		SettingsWidget->RemoveFromParent();
	}
	if (KeyBindingsWidget)
	{
		KeyBindingsWidget->RemoveFromParent();
	}
}
