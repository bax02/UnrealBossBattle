// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_AttackHit.h"
#include "DCharacter.h"
#include "DrawDebugHelpers.h"

void UDAnimNotify_AttackHit::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ADCharacter* Character = Cast<ADCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		FVector TraceStart = Character->GetMesh()->GetSocketLocation("Sword_Base");
		FVector TraceEnd = Character->GetMesh()->GetSocketLocation("Sword_Tip");

		FCollisionShape Shape;
		FVector Extent = FVector(100.f, 100.f, 100.f);

		Shape.SetCapsule(20.f, 65.0f);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Character);

		DrawDebugPoint(Character->GetWorld(), TraceStart, 8, FColor::Green, false, 2.0f);
		DrawDebugPoint(Character->GetWorld(), TraceEnd, 8, FColor::Green, false, 2.0f);
		DrawDebugLine(Character->GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
		FVector Center = ((TraceEnd - TraceStart).GetSafeNormal() * 70.0f) + TraceStart;
		//FVector Center = ((TraceEnd - TraceStart) / 2 + TraceStart);
		FVector Inter = TraceEnd - TraceStart;
		Inter.Normalize();

		FQuat MyQuat = Inter.ToOrientationQuat() * FQuat::MakeFromRotator(FRotator(90, 0, 0));
		UE_LOG(LogTemp, Log, TEXT("Start vector = %s"), *MyQuat.ToString());


		DrawDebugCapsule(Character->GetWorld(), Center, Shape.GetCapsuleHalfHeight(), Shape.GetCapsuleRadius(), MyQuat, FColor::Purple, false, 2.0f);
		FHitResult Hit;
		if (Character->GetWorld()->SweepSingleByObjectType(Hit, Center, Center, FQuat::Identity, ObjParams, Shape, Params))
		{
			FString Msg = FString::Printf(TEXT("Hit"));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, Msg);
		}

	}
}
