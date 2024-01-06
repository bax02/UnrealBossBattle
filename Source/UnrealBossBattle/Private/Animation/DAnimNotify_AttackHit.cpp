// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_AttackHit.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "DAttributeComponent.h"
#include "DActionComponent.h"
#include "DAction_Roll.h"
#include "Kismet/GameplayStatics.h"
#include "DCharacter.h"

void UDAnimNotify_AttackHit::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		FTransform TraceTransform = Character->GetMesh()->GetSocketTransform(TraceSocket);
		FVector TracePoint = TraceTransform.TransformPosition(LocationOffset);

		FCollisionShape Shape;

		Shape.SetSphere(SphereRadius);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Character);

		FHitResult Hit;
		if (Character->GetWorld()->SweepSingleByObjectType(Hit, TracePoint, TracePoint + FVector(0.1, 0.1, 0.1), FQuat::Identity, ObjParams, Shape, Params))
		{
			if (UDActionComponent::GetActions(Hit.GetActor())->IsActionOfClassRunning(UDAction_Roll::StaticClass()))
			{
				return;
			}
			DrawDebugSphere(Character->GetWorld(), TracePoint, SphereRadius, 16, FColor::Purple, false, 2.0f);
			// Spawn blood emitter
			FRotator Rotator = (Character->GetActorLocation() - Hit.ImpactPoint).ToOrientationRotator();
			DrawDebugPoint(Character->GetWorld(), Hit.ImpactPoint, 10.f, FColor::Red, false, 2.f, 0);
			UGameplayStatics::SpawnEmitterAtLocation(Character, HitParticles, Hit.ImpactPoint, Rotator, FVector(3, 3, 3), true, EPSCPoolMethod::AutoRelease, true);

			// Get the attribute component of the hit actor
			UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(Hit.GetActor());

			if (HitAttributeComp)
			{
				// Update the hit actors health
				HitAttributeComp->ApplyHealthChange(-20.f);
			}
			ADCharacter* HitCharacter = Cast<ADCharacter>(Hit.GetActor());
			if (HitCharacter)
			{
				HitCharacter->KnockbackStart(Character);
			}
		}

	}
}
