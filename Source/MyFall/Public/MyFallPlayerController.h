// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include <MyFall/MyFallGameModeBase.h>
#include "EnhancedInputComponent.h"
#include "MyFallPlayerController.generated.h"

class UUSerWidget;

UCLASS()
class MYFALL_API AMyFallPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn);

	UPROPERTY(BlueprintReadOnly)
	AMyFallGameModeBase* MyFallGameModeBase;

public:
	// Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMappingContext;

	void SetInputMappingContext();

	// Input modes
	UFUNCTION(BlueprintCallable)
	void SetInputModeUI();

	UFUNCTION(BlueprintCallable)
	void SetInputModeGame();

	// Widgets
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* PauseWidget;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* SettingsWidget;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* KeyBindingsWidget;

	// Win screen
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LevelEndScreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BlackscreenStartTransitionClass;

	void CreateWinScreen();

	// Widget to fade in from black screen at the start of each level
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BlackscreenEndTransitionClass;

private:
	// Input
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ActionPause = nullptr;

	UFUNCTION()
	void TriggerLevelTransition();

	UFUNCTION()
	void HandlePause();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	void DestroyPauseMenuWidgets();
};
