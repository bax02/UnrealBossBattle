// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/DAttributeComponent.h"
#include "GameFramework/Character.h"
#include "DGameModeBase.h"

// Sets default values for this component's properties
UDAttributeComponent::UDAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	Health = 100.f;
}

bool UDAttributeComponent::ApplyHealthChange(float Delta, AActor* InstigatorActor)
{

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	if (Health == 0.0f)
	{
		ADGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ADGameModeBase>();
		if (GameMode)
		{
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
		}
		return false;
	}

	return true;
}

UDAttributeComponent* UDAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UDAttributeComponent>();
	}
	return nullptr;
}
