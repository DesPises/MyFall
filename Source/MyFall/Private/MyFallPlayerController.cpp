// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFallPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyFallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
	AsMyFallGameModeBase = Cast<AMyFallGameModeBase>(CurrentGameMode);


}
