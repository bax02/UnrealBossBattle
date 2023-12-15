// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Block.h"
#include "GameFramework/Character.h"

void UDAction_Block::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		// Play animation and sound
		Character->PlayAnimMontage(BlockAnim);
		//UGameplayStatics::SpawnSoundAttached(AttackingSound, Character->GetMesh());

	}
}

void UDAction_Block::StopAction_Implementation(AActor* Instigator)
{
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->StopAnimMontage(BlockAnim);
	}
	Super::StopAction_Implementation(Instigator);
}

