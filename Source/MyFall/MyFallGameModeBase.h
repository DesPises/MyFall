// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyFallGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFALL_API AMyFallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OpenNextLevel(TSoftObjectPtr<UWorld> Level);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaitingForLevelTransition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLevel;
};
