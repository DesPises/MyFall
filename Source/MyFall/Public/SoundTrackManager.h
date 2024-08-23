// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundtrackManager.generated.h"

UCLASS()
class MYFALL_API ASoundtrackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundtrackManager();

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
	float FadeInDuration = 1.f;

	UPROPERTY(EditAnywhere)
	class USoundBase* MusicAsset;
};
