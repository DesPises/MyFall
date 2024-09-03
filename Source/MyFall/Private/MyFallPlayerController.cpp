// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFallPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <EnhancedInputSubsystems.h>
#include "Blueprint/UserWidget.h"
#include "InputActionValue.h"

void AMyFallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set defaults
	auto CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
	MyFallGameModeBase = Cast<AMyFallGameModeBase>(CurrentGameMode);

	SetInputMappingContext();

	// Fade in from black screen
	UUserWidget* BlackScreen = CreateWidget(this, BlackscreenEndTransitionClass);
	if (BlackScreen)
	{
		BlackScreen->AddToViewport();
	}
}

void AMyFallPlayerController::TriggerLevelTransition()
{
	if (MyFallGameModeBase->WaitingForLevelTransition)
	{
		MyFallGameModeBase->OpenNextLevel();
	}
}

void AMyFallPlayerController::HandlePause()
{
	if (MyFallGameModeBase)
	{
		if (UGameplayStatics::IsGamePaused(this))
		{
			UGameplayStatics::SetGamePaused(this, false);
			SetInputModeGame();
			DestroyPauseMenuWidgets();
		}
		else
		{
			UGameplayStatics::SetGamePaused(this, true);
			SetInputModeUI();
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

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	// Handle Level Transition input
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
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AMyFallPlayerController::SetInputModeUI()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AMyFallPlayerController::SetInputModeGame()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AMyFallPlayerController::CreateWinScreen()
{
	UUserWidget* BlackScreen = CreateWidget(this, BlackscreenStartTransitionClass);
	if (BlackScreen)
	{
		BlackScreen->AddToViewport();
	}

	UUserWidget* LevelEndScreen = CreateWidget(this, LevelEndScreenClass);
	if (LevelEndScreen)
	{
		LevelEndScreen->AddToViewport();
	}
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
