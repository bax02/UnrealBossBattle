// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DTutorialSpawner.generated.h"

class UDWorldUserWidget;
class ADDoor;

UCLASS()
class UNREALBOSSBATTLE_API ADTutorialSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADTutorialSpawner();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UDWorldUserWidget* DefaultWidgetInstance;

	UFUNCTION()
	void SpawnUI();

	UFUNCTION()
	void DestroySelf();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "DespawnInteractable")
	ADDoor* DoorInstance;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
