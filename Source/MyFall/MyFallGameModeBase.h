// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFallGameModeBase.generated.h"

class ASoundtrackManager;
class UUserWidget;
class ACPPBoris;
class AMyFallPlayerController;

UCLASS()
class MYFALL_API AMyFallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	ASoundtrackManager* SoundtrackManager;

	ACPPBoris* PlayerCharacterRef;
	AMyFallPlayerController* PlayerControllerRef;

	void ReadyForLevelTransition();

public:
	// Level transition
	UFUNCTION(BlueprintCallable)
	void OpenNextLevel();

	UFUNCTION(BlueprintCallable)
	void StartLevelTransition(const UWorld* NextLevelRef, const bool ApplauseSound);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WaitingForLevelTransition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NextLevel;

	// Input modes
	UFUNCTION(BlueprintCallable)
	void SetInputModeUI();

	UFUNCTION(BlueprintCallable)
	void SetInputModeGame();

	// Statistics
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statistics")
	int WorkedTraps = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statistics")
	int CollectedCoins = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statistics")
	int CoinsOnLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statistics")
	int TrapsActivatedByPlayer = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Statistics")
	int InitiallyInactiveTrapsOnLevel = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CollectibleClass;

	void CountCollectiblesOnLevel();
	void CountInactiveTraps();
	void CountWorkedTraps();
	
	// Misc
	UPROPERTY(EditAnywhere)
	USoundBase* ApplauseSoundAsset;

};
