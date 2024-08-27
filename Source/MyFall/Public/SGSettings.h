// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SGSettings.generated.h"

struct FEnhancedActionKeyMapping;

UCLASS()
class MYFALL_API USGSettings : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MusicVolume = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SFXVolume = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Sensitivity = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int GraphicsPresetIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Language = "en";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FEnhancedActionKeyMapping> KeyMappings;
};
