// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFallGameModeBase.h"

void AMyFallGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGame();
}

void AMyFallGameModeBase::OpenNextLevel(TSoftObjectPtr<UWorld> Level)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
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

void AMyFallGameModeBase::StartLevelTransition_Implementation(const UWorld* NextLevelPtr, const bool ApplauseSound)
{
	NextLevel = NextLevelPtr;
}


