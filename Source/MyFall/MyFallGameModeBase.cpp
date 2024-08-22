// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFallGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LevelFinish.h"

void AMyFallGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGame();
	UGameplayStatics::GetActorOfClass(this, ALevelFinish::StaticClass());
}

void AMyFallGameModeBase::OpenNextLevel()
{
	if (NextLevel)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);
	}
}

void AMyFallGameModeBase::StartLevelTransition_Implementation(const UWorld* NextLevelRef, const bool ApplauseSound)
{
	if (NextLevelRef)
	{
		NextLevel = NextLevelRef;
	}
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




