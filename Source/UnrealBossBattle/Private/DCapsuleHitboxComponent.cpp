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
#include "Kismet/KismetMathLibrary.h"

UDCapsuleHitboxComponent::UDCapsuleHitboxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	OwningCharacter = Cast<ACharacter>(GetOwner());
	Damage = 12.0f;
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
			FVector HitActorVector = Character->GetActorForwardVector();
			FVector Direction = (OwningCharacter->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal();

			double DotProduct = HitActorVector.Dot(Direction);

			double Result = UKismetMathLibrary::DegAcos(DotProduct);

			//UE_LOG(LogTemp, Log, TEXT("Result %f"), Result);
			// If the Hit Actor is facing the Owning Actor within 70 degrees then block
			if (Result < 70)
			{
				if (Character->OnBlock())
				{
					// We did not have enough stamina to block
					return;
				}
			}
		}

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
		
		SetGenerateOverlapEvents(false);

		#if !UE_BUILD_SHIPPING
		//DrawDebugCapsule(GetWorld(), GetComponentLocation(), GetScaledCapsuleHalfHeight(),
			//GetScaledCapsuleRadius(),GetComponentRotation().Quaternion(), FColor::Red, false, 2.0f);

		#endif
	}
}
