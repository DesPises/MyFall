// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class MYFALL_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrap();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WorkedOnEnemyAtLeastOnce;
};
