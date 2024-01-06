// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"
#include "DGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "DWorldUserWidget.h"

// Sets default values for this component's properties
UDInteractionComponent::UDInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceRadius = 20.0f;
	TraceDistance = 500.f;
	CollisionChannel = ECC_GameTraceChannel1;
}




// Called when the game starts
void UDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultWidgetInstance = CreateWidget<UDWorldUserWidget>(GetWorld(), DefaultWidgetClass);
	
}


// Called every frame
void UDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindBestInteractable();

}

void UDInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams Params;
	// Interactable Game Trace Channel
	Params.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, Params, Shape);

	FocusedActor = nullptr;

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<UDGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
		//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, FColor::Green, false, 2.0f);
	}

	if (FocusedActor)
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}



	//DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Green, false, 2.f, 0, 2.f);
}

void UDInteractionComponent::PrimaryInteract()
{
	if (FocusedActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor to Interact");
		return;
	}
	APawn* MyPawn = Cast<APawn>(GetOwner());
	
	IDGameplayInterface::Execute_Interact(FocusedActor, MyPawn);
}

