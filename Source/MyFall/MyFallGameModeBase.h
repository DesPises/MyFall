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
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void OpenNextLevel(TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintCallable)
	void SetInputModeUI();

	UFUNCTION(BlueprintCallable)
	void SetInputModeGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WaitingForLevelTransition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLevel;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartLevelTransition(const UWorld* NextLevelPtr, const bool ApplauseSound);
};
