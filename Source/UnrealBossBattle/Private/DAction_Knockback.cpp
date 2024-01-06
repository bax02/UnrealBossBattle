// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction_Knockback.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DActionComponent.h"
#include "DCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UDAction_Knockback::UDAction_Knockback()
{
	KnockbackAnimDelay = 1.2f;
	ImpulseStrength = 700.f;
	ZLaunchForce = 200;
}

void UDAction_Knockback::StartAction_Implementation(AActor* Instigator)
{
	Character = Cast<ADCharacter>(GetOwningComponent()->GetOwner());
	Super::StartAction_Implementation(Character);
	if (Character)
	{
		// Lock movement while in air
		Character->bCanMove = false;
		// Play animation and apply impulse
		FVector LaunchForce = (Character->GetActorLocation() - Instigator->GetActorLocation()).GetSafeNormal() * ImpulseStrength;
		LaunchForce.Z = ZLaunchForce;
		Character->PlayAnimMontage(KnockbackAnim);
		Character->LaunchCharacter(LaunchForce, true, true);

		FTimerHandle TimerHandle_KnockbackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "KnockbackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_KnockbackDelay, Delegate, KnockbackAnimDelay, false);
	}
}

void UDAction_Knockback::KnockbackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	UDActionComponent* ActionComp = UDActionComponent::GetActions(Character);
	if (ActionComp)
	{
		ActionComp->StartActionByName(InstigatorCharacter, "GetUp");
	}
	Super::StopAction_Implementation(InstigatorCharacter);
}