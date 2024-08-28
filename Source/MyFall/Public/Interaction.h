// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

UINTERFACE(MinimalAPI)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

class MYFALL_API IInteraction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact();
};
