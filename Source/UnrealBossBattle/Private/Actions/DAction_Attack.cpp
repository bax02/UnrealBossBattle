// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction_Attack.h"
#include "GameFramework/Character.h"
#include "Actions/DActionComponent.h"
#include "Attributes/DCharacterAttributeComponent.h"

bool UDAction_Attack::CanStart_Implementation(AActor* Instigator)
{
	UDActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	Character = Cast<ACharacter>(Instigator);
	CharacterAttributeComp = UDCharacterAttributeComponent::GetCharacterAttributes(Character);
	
	// Try and reduce Stamina

	if (!IsRunning())
	{
		return CharacterAttributeComp->ApplyStaminaChange(-6.f, 1.5f);
	}

	return true;
}

void UDAction_Attack::StartAction_Implementation(AActor* Instigator)
{
	if (!IsRunning())
	{
		Super::StartAction_Implementation(Instigator);

		if (Character)
		{
			// Play animation
			Character->PlayAnimMontage(AttackAnim);
		}
	}
	else
	{
		bContinueCombo = true;
	}
}

void UDAction_Attack::TryStopAction(AActor* Instigator)
{
	if (!bContinueCombo || comboCount == 2)
	{
		StopAction_Implementation(Instigator);
	}
	else {
		// Reduce Stamina
		if (CharacterAttributeComp)
		{
			CharacterAttributeComp->ApplyStaminaChange(-6.f, 1.5f);
		}
		comboCount++;
		bContinueCombo = false;
	}
}

void UDAction_Attack::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	if (Character)
	{
		Character->StopAnimMontage(AttackAnim);
	}
	comboCount = 0;
	bContinueCombo = false;
}