// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_AttackHit.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

void UDAnimNotify_AttackHit::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		FVector TraceStart = Character->GetMesh()->GetSocketLocation(TraceStartSocket);
		FVector TraceEnd = Character->GetMesh()->GetSocketLocation(TraceEndSocket);

		FCollisionShape Shape;

		Shape.SetCapsule(CapsuleRadius, CapsuleHalfHeight);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Character);

		DrawDebugPoint(Character->GetWorld(), TraceStart, 8, FColor::Green, false, 2.0f);
		DrawDebugPoint(Character->GetWorld(), TraceEnd, 8, FColor::Green, false, 2.0f);
		DrawDebugLine(Character->GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
		FVector Center = ((TraceEnd - TraceStart).GetSafeNormal() * CapsuleHalfHeight) + TraceStart;
		FVector Inter = TraceEnd - TraceStart;
		Inter.Normalize();

		FQuat RotQuat = Inter.ToOrientationQuat() * FQuat::MakeFromRotator(FRotator(90, 0, 0));

		DrawDebugCapsule(Character->GetWorld(), Center, Shape.GetCapsuleHalfHeight(), Shape.GetCapsuleRadius(), RotQuat, FColor::Purple, false, 2.0f);
		FHitResult Hit;
		if (Character->GetWorld()->SweepSingleByObjectType(Hit, Center, Center, RotQuat, ObjParams, Shape, Params))
		{
			FString Msg = FString::Printf(TEXT("Hit"));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, Msg);
		}

	}
}
