// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DCapsuleHitboxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Attributes/DAttributeComponent.h"
#include "DCharacter.h"

UDCapsuleHitboxComponent::UDCapsuleHitboxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Damage = 12.0f;
}

void UDCapsuleHitboxComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<ACharacter>(GetOwner());

	this->OnComponentBeginOverlap.AddDynamic(this, &UDCapsuleHitboxComponent::OnOverlap);
}

void UDCapsuleHitboxComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != OwningCharacter)
	{
		// Stop hitbox from hitting anything else this swing
		SetGenerateOverlapEvents(false);

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
			UGameplayStatics::SpawnEmitterAtLocation(OwningCharacter, HitParticles, Hit.ImpactPoint, GetComponentRotation(), FVector(2.2, 2.2, 2.2), true, EPSCPoolMethod::AutoRelease, true);

		}

		// Get the attribute component of the hit actor
		UDAttributeComponent* HitAttributeComp = UDAttributeComponent::GetAttributes(OtherActor);

		ADCharacter* Character = Cast<ADCharacter>(OtherActor);

		if (HitAttributeComp)
		{
			// Update the hit actors health
			if (HitAttributeComp->ApplyHealthChange(-Damage, OwningCharacter))
			{
				if (Character)
				{
					Character->KnockbackStart(OwningCharacter);
				}
			}
		}

		#if !UE_BUILD_SHIPPING
		//DrawDebugCapsule(GetWorld(), GetComponentLocation(), GetScaledCapsuleHalfHeight(),
			//GetScaledCapsuleRadius(),GetComponentRotation().Quaternion(), FColor::Red, false, 2.0f);

		#endif
	}
}
