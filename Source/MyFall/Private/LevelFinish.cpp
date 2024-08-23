// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFinish.h"
#include "Components/BoxComponent.h"

ALevelFinish::ALevelFinish()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
}

void ALevelFinish::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelFinish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

