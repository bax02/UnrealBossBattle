// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGameplayInterface.h"
#include "DDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorInteract);

UCLASS()
class UNREALBOSSBATTLE_API ADDoor : public AActor, public IDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDoor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FVector TeleportOffset;

	UPROPERTY(BlueprintAssignable)
	FOnDoorInteract OnDoorInteract;

	void Interact_Implementation(APawn* InstigatorPawn) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
