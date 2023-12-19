// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_BossCombo.h"
#include "GameFramework/Character.h"

void UDAction_BossCombo::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		// Play animation and sound
		Character->PlayAnimMontage(ComboAnim);

		FTimerHandle TimerHandle_ComboDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ComboDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ComboDelay, Delegate, ComboAnim->GetPlayLength(), false);
	}
}
void UDAction_BossCombo::ComboDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	StopAction(InstigatorCharacter);
}