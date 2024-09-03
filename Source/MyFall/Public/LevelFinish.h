// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelFinish.generated.h"

class UBoxComponent;

UCLASS()
class MYFALL_API ALevelFinish : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelFinish();

private:
	UBoxComponent* BoxCollision = nullptr;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
	int LevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelInfo")
	TSoftObjectPtr<UWorld> NextLevel;
};
