// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Attack.h"
#include "GameFramework/Character.h"
#include "DActionComponent.h"

bool UDAction_Attack::CanStart_Implementation(AActor* Instigator)
{
	UDActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

void UDAction_Attack::StartAction_Implementation(AActor* Instigator)
{
	if (!IsRunning())
	{
		Super::StartAction_Implementation(Instigator);
		ACharacter* Character = Cast<ACharacter>(Instigator);
		if (Character)
		{
			// Play animation and sound
			Character->PlayAnimMontage(AttackAnim);
			//UGameplayStatics::SpawnSoundAttached(AttackingSound, Character->GetMesh());
		}
	}
	else
	{
		bContinueCombo = true;
	}
}

void UDAction_Attack::StopAction_Implementation(AActor* Instigator)
{
	if (!bContinueCombo || comboCount == 2)
	{
		Super::StopAction_Implementation(Instigator);
		ACharacter* Character = Cast<ACharacter>(Instigator);
		if (Character)
		{
			Character->StopAnimMontage(AttackAnim);
		}
		comboCount = 0;
		bContinueCombo = false;

	}
	else {
		comboCount++;
		bContinueCombo = false;
	}

}