// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacterAttributeComponent.h"
#include "DAction_Sprint.h"
#include "DCharacter.h"
#include "DActionComponent.h"

UDCharacterAttributeComponent::UDCharacterAttributeComponent()
{
	MaxStamina = 75;
	Stamina = MaxStamina;

	MaxPotions = 4;
	Potions = MaxPotions;
}

void UDCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<ADCharacter>(GetOwner());
	if (ensure(OwningCharacter))
	{
		OwningActionComp = UDActionComponent::GetActions(OwningCharacter);
		ensure(OwningActionComp);
	}
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "UpdateStamina");

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateStamina, Delegate, 0.08f, true);
}

void UDCharacterAttributeComponent::UpdateStamina()
{
	float StaminaChange = 0;
	float Cooldown = 0;
	if (OwningActionComp->IsActionOfClassRunning(UDAction_Sprint::StaticClass()))
	{
		// We are sprinting
		StaminaChange = -0.25f;
		// Set cooldown for regenerating stamina
		Cooldown = 0.4f;
	}
	else if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_StaminaCooldown)){
		// We are not in a cooldown so we can regenerate stamina
		StaminaChange = 3.f;
	}
	if (!ApplyStaminaChange(StaminaChange, Cooldown))
	{
		// We do not have enough stamina to sprint
		OwningActionComp->StopActionByName(OwningCharacter, "Sprint");
	}
}

bool UDCharacterAttributeComponent::ApplyStaminaChange(float Delta, float Cooldown)
{
	if (Stamina + Delta < 0.0f)
	{
		return false;
	}
	Stamina = FMath::Clamp(Stamina + Delta, 0.0f, MaxStamina);

	OnStaminaChanged.Broadcast(nullptr, this, Stamina, Delta);

	if (Cooldown > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_StaminaCooldown, Cooldown, false);
	}

	return true;
}

bool UDCharacterAttributeComponent::ApplyPotionChange(int Delta)
{
	if (Potions + Delta < 0)
	{
		return false;
	}

	Potions = FMath::Clamp(Potions + Delta, 0, MaxPotions);

	OnPotionChanged.Broadcast(this, Potions);

	return true;
}

UDCharacterAttributeComponent* UDCharacterAttributeComponent::GetCharacterAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UDCharacterAttributeComponent>();
	}
	return nullptr;
}