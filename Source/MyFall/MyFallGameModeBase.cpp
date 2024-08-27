// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFallGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LevelFinish.h"
#include "SoundtrackManager.h"
#include "Trap.h"
#include "CPPBoris.h"
#include "MyFallPlayerController.h"

void AMyFallGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGame();
	
	// Defaults
	PlayerCharacterRef = Cast<ACPPBoris>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerControllerRef = Cast<AMyFallPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	CountCollectiblesOnLevel();
	CountInactiveTraps();
}

void AMyFallGameModeBase::OpenNextLevel()
{
	if (NextLevel)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);
	}
}

void AMyFallGameModeBase::StartLevelTransition(const UWorld* NextLevelRef, const bool ApplauseSound)
{
	if (PlayerCharacterRef)
	{
		PlayerCharacterRef->DisableMovement();
	}

	if (NextLevelRef)
	{
		NextLevel = NextLevelRef;
	}

	if (SoundtrackManager)
	{
		SoundtrackManager->FadeMusicOut();
	}
	if (ApplauseSound)
	{
		UGameplayStatics::PlaySound2D(this, ApplauseSoundAsset);
	}

	// Count worked traps for end level statistics
	CountWorkedTraps();

	// Crteate win screen
	if (PlayerControllerRef)
	{
		PlayerControllerRef->CreateWinScreen();
	}

	// Set is ready for level transition W/ 1.5 sec delay
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyFallGameModeBase::ReadyForLevelTransition, 1.5f, false);
}

void AMyFallGameModeBase::ReadyForLevelTransition()
{
	WaitingForLevelTransition = true;
}

void AMyFallGameModeBase::SetInputModeUI()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
}

void AMyFallGameModeBase::SetInputModeGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

void AMyFallGameModeBase::CountCollectiblesOnLevel()
{
	TArray<AActor*> Collectibles;
	UGameplayStatics::GetAllActorsOfClass(this, CollectibleClass, Collectibles);
	if (Collectibles.Num() > 0)
	{
		CoinsOnLevel = Collectibles.Num();
	}
}

void AMyFallGameModeBase::CountInactiveTraps()
{
	InitiallyInactiveTrapsOnLevel = 0;
	TSubclassOf<ATrap> TrapClass;
	TArray<AActor*> Traps;

	UGameplayStatics::GetAllActorsOfClass(this, TrapClass, Traps);
	for (AActor* Trap : Traps)
	{
		if (Cast<ATrap>(Trap)->IsActive)
		{
			InitiallyInactiveTrapsOnLevel++;
		}
	}
}

void AMyFallGameModeBase::CountWorkedTraps()
{
	TArray<AActor*> TrapsOnLevel;
	UGameplayStatics::GetAllActorsOfClass(this, ATrap::StaticClass(), TrapsOnLevel);
	if (TrapsOnLevel.Num() >= 0)
	{
		for (AActor* Trap : TrapsOnLevel)
		{
			if (Cast<ATrap>(Trap)->WorkedOnEnemyAtLeastOnce)
			{
				WorkedTraps++;
			}
		}
	}
}




