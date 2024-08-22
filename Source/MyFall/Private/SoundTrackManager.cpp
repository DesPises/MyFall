// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTrackManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ASoundTrackManager::ASoundTrackManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASoundTrackManager::FadeMusicIn()
{
	if (MusicAsset)
	{
		AudioComponent->FadeIn(FadeInDuration);
	}
}

void ASoundTrackManager::FadeMusicOut()
{
	if (MusicAsset)
	{
		AudioComponent->FadeOut(1.f, 0);
	}
}

void ASoundTrackManager::BeginPlay()
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



