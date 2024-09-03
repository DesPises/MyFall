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

void ASoundtrackManager::LowPitch()
{
	AudioComponent->SetPitchMultiplier(0.98f);
	AudioComponent->SetVolumeMultiplier(0.5f);
}

void ASoundtrackManager::NormalPitch()
{
	AudioComponent->SetPitchMultiplier(1.f);
	AudioComponent->SetVolumeMultiplier(1.f);
}

void ASoundtrackManager::HighPitch()
{
	AudioComponent->SetPitchMultiplier(1.01f);
	AudioComponent->SetVolumeMultiplier(0.5f);
}

void ASoundtrackManager::StopMusic()
{
	AudioComponent->FadeOut(1.f, 0.f);
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



