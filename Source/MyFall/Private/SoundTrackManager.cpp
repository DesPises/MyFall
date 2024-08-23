// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTrackManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ASoundtrackManager::ASoundtrackManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASoundtrackManager::FadeMusicIn()
{
	if (MusicAsset)
	{
		AudioComponent->FadeIn(FadeInDuration);
	}
}

void ASoundtrackManager::FadeMusicOut()
{
	if (MusicAsset)
	{
		AudioComponent->FadeOut(1.f, 0);
	}
}

void ASoundtrackManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (MusicAsset)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(this, MusicAsset);
		if (AudioComponent)
		{
			FadeMusicIn();
		}
	}
}



