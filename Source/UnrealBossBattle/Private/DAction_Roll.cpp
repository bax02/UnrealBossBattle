// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Roll.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DCharacterAttributeComponent.h"

UDAction_Roll::UDAction_Roll()
{
	//1.464f
	RollAnimDelay = 0.5f;
	StaminaCost = -10.f;
}

bool UDAction_Roll::CanStart_Implementation(AActor* Instigator)
{
	if (Super::CanStart_Implementation(Instigator))
	{
		Character = Cast<ACharacter>(Instigator);
		CharacterAttributeComp = UDCharacterAttributeComponent::GetCharacterAttributes(Character);

		// Try and reduce Stamina

		if (CharacterAttributeComp->ApplyStaminaChange(StaminaCost, 1.5f))
		{
			return true;
		}
	}

	return false;
}

void UDAction_Roll::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
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
	if (bIsRunning)
	{
		StopAction_Implementation(InstigatorCharacter);
	}
}
void UDAction_Roll::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	if (Character)
	{
		Character->StopAnimMontage(RollAnim);
	}

}

