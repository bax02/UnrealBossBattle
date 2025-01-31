// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADDoor::ADDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	RootComponent = DoorMesh;

}

// Called when the game starts or when spawned
void ADDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADDoor::Interact_Implementation(APawn* InstigatorPawn)
{
	OnDoorInteract.Broadcast();
	// Check if the instigator is in front of the door
	// Teleport the instigator pawn behind the door
	if (InstigatorPawn->TeleportTo(GetActorLocation() + TeleportOffset, InstigatorPawn->GetActorRotation(), false, true))
	{
		// Make the door not interactable anymore
		DoorMesh->SetCollisionObjectType(ECC_WorldDynamic);
	}

}

