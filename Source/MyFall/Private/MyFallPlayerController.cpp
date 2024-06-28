// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFallPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <EnhancedInputSubsystems.h>


void AMyFallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
	AsMyFallGameModeBase = Cast<AMyFallGameModeBase>(CurrentGameMode);

	SetInputMappingContext();
}

void AMyFallPlayerController::SetInputMappingContext()
{
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);
}
