// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction.h"
#include "Actions/DActionComponent.h"
#include "Actions/DAction_Sprint.h"

bool UDAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}
	UDActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

void UDAction::StartAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	for (FName name : CancelsNames)
	{
		Comp->StopActionByName(Instigator, name);
	}

	bIsRunning = true;
}

void UDAction::StopAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	
	if (Comp->bSprintInputBuffer && !this->IsA(UDAction_Sprint::StaticClass()))
	{
		Comp->StartActionByName(Instigator, "Sprint");
	}

	bIsRunning = false;
}

UDActionComponent* UDAction::GetOwningComponent() const
{
	return Cast<UDActionComponent>(GetOuter());
}

bool UDAction::IsRunning() const
{
	return bIsRunning;
}