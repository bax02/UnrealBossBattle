// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DAction_GetUp.h"
#include "DCharacter.h"
#include "Actions/DActionComponent.h"


UDAction_GetUp::UDAction_GetUp()
{
	GetUpAnimDelay = 1.3f;
}

void UDAction_GetUp::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	Character = Cast<ADCharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(GetUpAnim);
		FTimerHandle TimerHandle_GetUpDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "GetUpDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_GetUpDelay, Delegate, GetUpAnimDelay, false);
	}
}

void UDAction_GetUp::GetUpDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (bIsRunning)
	{
		StopAction_Implementation(InstigatorCharacter);
	}
}

void UDAction_GetUp::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	if (Character)
	{
		Character->bCanMove = true;
	}
}

