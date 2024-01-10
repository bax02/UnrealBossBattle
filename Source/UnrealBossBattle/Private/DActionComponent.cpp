// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"
#include "DAction.h"

UDActionComponent::UDActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UDAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
	
}

void UDActionComponent::AddAction(TSubclassOf<UDAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UDAction* NewAction = NewObject<UDAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UDActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				#if !UE_BUILD_SHIPPING
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				#endif
				continue;
			}
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UDActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

UDAction* UDActionComponent::GetAction(TSubclassOf<UDAction> ActionClass) const
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

bool UDActionComponent::IsActionOfClassRunning(TSubclassOf<UDAction> ActionClass)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			if (Action->IsRunning())
			{
				return true;
			}
		}
	}

	return false;
}

UDActionComponent* UDActionComponent::GetActions(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UDActionComponent>();
	}
	return nullptr;
}