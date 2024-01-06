// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_LaunchForwards.h"
#include "AI/DAICharacter.h"

void UDAnimNotify_LaunchForwards::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ADAICharacter* Character = Cast<ADAICharacter>(MeshComp->GetOwner());
	if (Character)
	{
		FVector LaunchVector = Character->GetViewRotation().Vector().GetSafeNormal() * 1000.f;
		LaunchVector.Z = 0.f;

		Character->LaunchCharacter(LaunchVector, true, false);
	}

}
