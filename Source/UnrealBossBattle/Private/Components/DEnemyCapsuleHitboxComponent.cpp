// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DEnemyCapsuleHitboxComponent.h"
#include "DCharacter.h"
#include "Actions/DActionComponent.h"
#include "Actions/DAction_Roll.h"
#include "Actions/DAction_Block.h"
#include "Kismet/KismetMathLibrary.h"

void UDEnemyCapsuleHitboxComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != OwningCharacter)
	{
		// Stop hitbox from hitting anything else this swing
		SetGenerateOverlapEvents(false);

		ADCharacter* Character = Cast<ADCharacter>(OtherActor);
		if (Character && UDActionComponent::GetActions(Character)->IsActionOfClassRunning(UDAction_Roll::StaticClass()))
		{
			return;
		}

		if (Character && UDActionComponent::GetActions(Character)->IsActionOfClassRunning(UDAction_Block::StaticClass()))
		{
			FVector HitActorVector = Character->GetActorForwardVector();
			FVector Direction = (OwningCharacter->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal();

			double DotProduct = HitActorVector.Dot(Direction);

			double Result = UKismetMathLibrary::DegAcos(DotProduct);

			// If the Hit Actor is facing the Owning Actor within 90 degrees then block
			if (Result < 90)
			{
				if (Character->OnBlock())
				{
					// We did not have enough stamina to block
					return;
				}
			}
		}
		Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
