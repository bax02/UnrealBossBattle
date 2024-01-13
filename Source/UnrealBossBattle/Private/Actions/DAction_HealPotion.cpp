// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction_HealPotion.h"
#include "GameFramework/Character.h"
#include "Attributes/DCharacterAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

UDAction_HealPotion::UDAction_HealPotion()
{
	HealAmount = 40.f;
	HealAnimDelay = 3.4f;
}

bool UDAction_HealPotion::CanStart_Implementation(AActor* Instigator)
{
	if (Super::CanStart_Implementation(Instigator))
	{
		Character = Cast<ACharacter>(Instigator);
		CharacterAttributeComp = UDCharacterAttributeComponent::GetCharacterAttributes(Character);

		// Try and reduce Potions

		if (CharacterAttributeComp->ApplyPotionChange(-1))
		{
			return true;
		}
	}

	return false;
}

void UDAction_HealPotion::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (Character)
	{
		// Hide Shield
		Character->GetMesh()->HideBoneByName(BoneName, PBO_None);

		// Play animation and sound
		Character->PlayAnimMontage(HealAnim);

		FTimerHandle TimerHandle_HealDelay;
		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "HealDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_HealDelay, Delegate, HealAnimDelay, false);

		FTimerHandle TimerHandle_ApplyHealDelay;

		Delegate.BindUFunction(this, "ApplyHealDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ApplyHealDelay, Delegate, 2.0f, false);
	}
}

void UDAction_HealPotion::HealDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (bIsRunning)
	{
		StopAction_Implementation(InstigatorCharacter);
	}
}


void UDAction_HealPotion::ApplyHealDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	// Increase Health
	if (CharacterAttributeComp)
	{
		CharacterAttributeComp->ApplyHealthChange(HealAmount, InstigatorCharacter);
	}
}

void UDAction_HealPotion::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	if (Character)
	{
		// Show Shield
		Character->GetMesh()->UnHideBoneByName(BoneName);
		// Stop Anim Montage
		Character->StopAnimMontage(HealAnim);
	}
}
