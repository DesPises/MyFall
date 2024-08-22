// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundTrackManager.generated.h"

UCLASS()
class MYFALL_API ASoundTrackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundTrackManager();

	UFUNCTION(BlueprintCallable)
	void FadeMusicIn();
	UFUNCTION(BlueprintCallable)
	void FadeMusicOut();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	float FadeInDuration;

	UPROPERTY(EditAnywhere)
	class USoundBase* MusicAsset;
};
