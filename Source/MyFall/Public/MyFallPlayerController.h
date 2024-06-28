// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include <MyFall/MyFallGameModeBase.h>
#include "MyFallPlayerController.generated.h"

UCLASS()
class MYFALL_API AMyFallPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly)
	AMyFallGameModeBase* AsMyFallGameModeBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMappingContext;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
};
