// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFallGameInstance.h"
#include "SGSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "GameFramework/GameUserSettings.h"

void UMyFallGameInstance::SaveSettings()
{
	UGameplayStatics::SaveGameToSlot(SettingsSaveObject, SettingsSaveGameName, 0);
}

void UMyFallGameInstance::Init()
{
	LoadSettings();
}

void UMyFallGameInstance::LoadSettings()
{
	if (UGameplayStatics::DoesSaveGameExist(SettingsSaveGameName, 0))
	{
		SettingsSaveObject = Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(
					SettingsSaveGameName, 0));
	
		// Set language
		UKismetInternationalizationLibrary::SetCurrentCulture(SettingsSaveObject->Language, true);
		// Set Graphics preset
		UGameUserSettings::GetGameUserSettings()->SetOverallScalabilityLevel(SettingsSaveObject->GraphicsPresetIndex);
		UGameUserSettings::GetGameUserSettings()->ApplySettings(true);
	}
	else
	{
		UGameplayStatics::CreateSaveGameObject(USGSettings::StaticClass());
		LoadSettings();
	}
}
