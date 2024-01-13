// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction_Sprint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Attributes/DCharacterAttributeComponent.h"

void UDAction_Sprint::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	UCharacterMovementComponent* MovementComp = Instigator->GetComponentByClass<UCharacterMovementComponent>();
	CharacterAttributeComp = Instigator->GetComponentByClass<UDCharacterAttributeComponent>();
	if (ensure(MovementComp))
	{
		if (ensure(CharacterAttributeComp))
		{
			MovementComp->MaxWalkSpeed = MovementComp->MaxWalkSpeed + BonusSpeed;
		}
	}
}

void UDAction_Sprint::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	UCharacterMovementComponent* MovementComp = Instigator->GetComponentByClass<UCharacterMovementComponent>();
	if (ensure(MovementComp))
	{

		MovementComp->MaxWalkSpeed = MovementComp->MaxWalkSpeed - BonusSpeed;
	}
}
