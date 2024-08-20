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

	UFUNCTION()
	void TriggerLevelTransition();
	UFUNCTION()
	void HandlePause();

	virtual void OnPossess(APawn* aPawn);

public:
	UPROPERTY(BlueprintReadOnly)
	AMyFallGameModeBase* AsMyFallGameModeBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMappingContext;

	void SetInputMappingContext();

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* PauseWidget;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* SettingsWidget;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* KeyBindingsWidget;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ActionJump = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* ActionPause = nullptr;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	void DestroyPauseMenuWidgets();
};
