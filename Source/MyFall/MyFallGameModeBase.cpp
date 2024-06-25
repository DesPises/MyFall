// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFallGameModeBase.h"

void AMyFallGameModeBase::OpenNextLevel(TSoftObjectPtr<UWorld> Level)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
}
