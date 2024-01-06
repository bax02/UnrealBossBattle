// Fill out your copyright notice in the Description page of Project Settings.


#include "DCapsuleHitboxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DAttributeComponent.h"
#include "DCharacter.h"
#include "DrawDebugHelpers.h"
#include "DActionComponent.h"
#include "DAction_Roll.h"
#include "DAction_Block.h"

UDCapsuleHitboxComponent::UDCapsuleHitboxComponent()
{
	OwningCharacter = Cast<ACharacter>(GetOwner());
	ensure(OwningCharacter);
}

void UDCapsuleHitboxComponent::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentBeginOverlap.AddDynamic(this, &UDCapsuleHitboxComponent::OnOverlap);
}

void UDCapsuleHitboxComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != OwningCharacter)
	{
		ADCharacter* Character = Cast<ADCharacter>(OtherActor);
		if (Character && UDActionComponent::GetActions(Character)->IsActionOfClassRunning(UDAction_Roll::StaticClass()))
		{
			return;
		}

		if (Character && UDActionComponent::GetActions(Character)->IsActionOfClassRunning(UDAction_Block::StaticClass()))
		{
			UDAction_Block::BlockHit(Character, BlockParticles, BlockSound);
			return;
		}
		DrawDebugCapsule(GetWorld(), GetComponentLocation(), GetScaledCapsuleHalfHeight(),
			GetScaledCapsuleRadius(),GetComponentRotation().Quaternion(), FColor::Red, false, 2.0f);

		// Play the hit sound
		UGameplayStatics::SpawnSoundAttached(HitSound, this);

		// Perform a capsule sweep to get the location of the hit as OnComponentBeginOverlap does not provide this
		FCollisionShape Shape;
		Shape.SetCapsule(GetScaledCapsuleRadius() * 1.1f, GetScaledCapsuleHalfHeight() * 1.1f);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(OwningCharacter);

		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, GetComponentLocation(), GetComponentLocation() + FVector(0.1, 0.1, 0.1), GetComponentRotation().Quaternion(), ObjParams, Shape, Params))
		{
			//FRotator Rotator = (OwningCharacter->GetActorLocation() - Hit.ImpactPoint).ToOrientationRotator();
			//Rotator.Pitch = -80;
			//UE_LOG(LogTemp, Log, TEXT("Rotator: %s"), *Rotator.ToString());
			//DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 10.f, FColor::Green, false, 2.f, 0);
			//DrawDebugCoordinateSystem(GetWorld(), Hit.ImpactPoint, GetComponentRotation(), 50.f, false, 2.f, 0);
			// Spawn particle effect at the location of the hit and with the rotation facing away form the hit actor
			UGameplayStatics::SpawnEmitterAtLocation(OwningCharacter, HitParticles, Hit.ImpactPoint, GetComponentRotation(), FVector(2.2, 2.2, 2.2), true, EPSCPoolMethod::AutoRelease, true);

		}

		// Get the attribute component of the hit actor
		UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(OtherActor);

		if (HitAttributeComp)
		{
			// Update the hit actors health
			HitAttributeComp->ApplyHealthChange(-20.f);
		}

		if (Character)
		{
			Character->KnockbackStart(OwningCharacter);
		}
		SetGenerateOverlapEvents(false);
	}
}
