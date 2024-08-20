// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTrackManager.h"

// Sets default values
ASoundTrackManager::ASoundTrackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundTrackManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundTrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

