// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Sprint.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDAction_Sprint::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	UCharacterMovementComponent* MovementComp = Instigator->GetComponentByClass<UCharacterMovementComponent>();
	if (ensure(MovementComp))
	{
		MovementComp->MaxWalkSpeed = MovementComp->MaxWalkSpeed + BonusSpeed;
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
