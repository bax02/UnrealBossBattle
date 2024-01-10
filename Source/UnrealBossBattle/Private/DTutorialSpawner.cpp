// Fill out your copyright notice in the Description page of Project Settings.


#include "DTutorialSpawner.h"
#include "DWorldUserWidget.h"
#include "DGameModeBase.h"
#include "DDoor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADTutorialSpawner::ADTutorialSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADTutorialSpawner::BeginPlay()
{
	Super::BeginPlay();

	ADGameModeBase* GameMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		GameMode->OnGameStart.AddDynamic(this, &ADTutorialSpawner::SpawnUI);
	}

	if (DoorInstance)
	{
		DoorInstance->OnDoorInteract.AddDynamic(this, &ADTutorialSpawner::DestroySelf);
	}
}

void ADTutorialSpawner::SpawnUI()
{
	DefaultWidgetInstance = CreateWidget<UDWorldUserWidget>(GetWorld(), DefaultWidgetClass);
	if (DefaultWidgetInstance)
	{
		DefaultWidgetInstance->AttachedActor = this;
		DefaultWidgetInstance->AddToViewport();
	}
}

void ADTutorialSpawner::DestroySelf()
{
	Super::Destroy();
}