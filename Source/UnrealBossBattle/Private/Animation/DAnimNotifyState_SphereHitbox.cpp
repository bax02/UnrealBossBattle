// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotifyState_SphereHitbox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Actions/DActionComponent.h"
#include "Actions/DAction_Roll.h"
#include "Attributes/DAttributeComponent.h"
#include "DCharacter.h"

void UDAnimNotifyState_SphereHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		// Setup location and shape for hitbox
		FTransform TraceTransform = Character->GetMesh()->GetSocketTransform(TraceSocket);
		TracePoint = TraceTransform.TransformPosition(LocationOffset);

		Shape.SetSphere(SphereRadius);
		Params.AddIgnoredActor(Character);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		// Set a timer to perform a sweep at a specific interval
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "UpdateHitbox");
		Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateHitbox, Delegate, 0.1f, true);
	}



}

void UDAnimNotifyState_SphereHitbox::UpdateHitbox() 
{
	if (Character)
	{
		FHitResult Hit;
		if (Character->GetWorld()->SweepSingleByObjectType(Hit, TracePoint, TracePoint + FVector(0.1, 0.1, 0.1), FQuat::Identity, ObjParams, Shape, Params))
		{
			if (UDActionComponent::GetActions(Hit.GetActor())->IsActionOfClassRunning(UDAction_Roll::StaticClass()))
			{
				return;
			}
			// We have hit the hit actor while they are not immune, cancel timer
			Character->GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateHitbox);

			//DrawDebugSphere(Character->GetWorld(), TracePoint, SphereRadius, 16, FColor::Purple, false, 2.0f);

			//PLay Hit sound
			UGameplayStatics::SpawnSoundAtLocation(Character, HitSound, Hit.ImpactPoint);

			// Spawn blood emitter
			FRotator Rotator = (Character->GetActorLocation() - Hit.ImpactPoint).ToOrientationRotator();
			//DrawDebugPoint(Character->GetWorld(), Hit.ImpactPoint, 10.f, FColor::Red, false, 2.f, 0);
			UGameplayStatics::SpawnEmitterAtLocation(Character, HitParticles, Hit.ImpactPoint, Rotator, FVector(3, 3, 3), true, EPSCPoolMethod::AutoRelease, true);

			// Get the attribute component of the hit actor
			UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(Hit.GetActor());

			if (HitAttributeComp)
			{
				// Update the hit actors health
				if (HitAttributeComp->ApplyHealthChange(-40.f, Character))
				{
					ADCharacter* HitCharacter = Cast<ADCharacter>(Hit.GetActor());

					if (HitCharacter)
					{
						HitCharacter->KnockbackStart(Character);
					}
				}
			}
		}
	}
}



void UDAnimNotifyState_SphereHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Cancel timer
	Character->GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateHitbox);

}
