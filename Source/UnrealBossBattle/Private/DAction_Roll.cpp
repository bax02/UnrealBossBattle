// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Roll.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UDAction_Roll::UDAction_Roll()
{
	//1.464f
	RollAnimDelay = 0.5f;
}

void UDAction_Roll::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		// Play animation and sound
		Character->PlayAnimMontage(RollAnim);
		UGameplayStatics::SpawnSoundAttached(RollingSound, Character->GetMesh());

		FTimerHandle TimerHandle_RollDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RollDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_RollDelay, Delegate, RollAnimDelay, false);
	}
}
void UDAction_Roll::RollDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	StopAction(InstigatorCharacter);
}
