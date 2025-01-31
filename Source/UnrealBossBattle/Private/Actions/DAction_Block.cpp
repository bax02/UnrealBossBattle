// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction_Block.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Attributes/DCharacterAttributeComponent.h"

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