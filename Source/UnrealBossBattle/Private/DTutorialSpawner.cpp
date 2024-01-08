// Fill out your copyright notice in the Description page of Project Settings.


#include "DTutorialSpawner.h"
#include "DWorldUserWidget.h"
#include "DGameModeBase.h"
#include "DDoor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADTutorialSpawner::ADTutorialSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void ADTutorialSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

