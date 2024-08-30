// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyFallGameInstance.generated.h"

class USGSettings;

UCLASS()
class MYFALL_API UMyFallGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Settings save object

	UFUNCTION(BlueprintCallable)
	void SaveSettings();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USGSettings* SettingsSaveObject;

protected:
	virtual void Init() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FString SettingsSaveGameName;

	UFUNCTION()
	void LoadSettings();
};
