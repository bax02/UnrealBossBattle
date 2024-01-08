// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Block.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DCharacterAttributeComponent.h"

void UDAction_Block::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		// Play animation and sound
		Character->PlayAnimMontage(BlockAnim);
		UGameplayStatics::SpawnSoundAttached(BlockingSound, Character->GetMesh());

	}
}

void UDAction_Block::StopAction_Implementation(AActor* Instigator)
{
	if (Character)
	{
		Character->StopAnimMontage(BlockAnim);
	}
	Super::StopAction_Implementation(Instigator);
}

bool UDAction_Block::BlockHit(ACharacter* HitCharacter, UParticleSystem* HitParticles, USoundBase* HitSound)
{
	if (HitCharacter)
	{
		UDCharacterAttributeComponent* AttributeComp = UDCharacterAttributeComponent::GetCharacterAttributes(HitCharacter);
		if (AttributeComp)
		{
			if (!AttributeComp->ApplyStaminaChange(-15.f, 1.5f))
			{
				// We do not have enough stamina to block return false and break guard
				// TODO Break guard (Stop Action). Hard as we are in a static function. May make this function non static
				// or put it in character class.
				return false;
			}
		}
		UGameplayStatics::SpawnSoundAttached(HitSound, HitCharacter->GetMesh());
		UGameplayStatics::SpawnEmitterAttached(HitParticles, HitCharacter->GetMesh(), "ShieldCenter");
	}
	return true;
}

