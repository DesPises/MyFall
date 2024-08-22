// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFallGameModeBase.generated.h"

class ASoundTrackManager;

UCLASS()
class MYFALL_API AMyFallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	ASoundTrackManager* SoundtrackManager;

public:
	UFUNCTION(BlueprintCallable)
	void OpenNextLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartLevelTransition(const UWorld* NextLevelRef, const bool ApplauseSound);

	UFUNCTION(BlueprintCallable)
	void SetInputModeUI();

	UFUNCTION(BlueprintCallable)
	void SetInputModeGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WaitingForLevelTransition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLevel;

};
