// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_HideBone.h"

void UDAnimNotify_HideBone::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!bShowBone)
	{
		MeshComp->HideBoneByName(BoneName, PBO_None);
	}
	else
	{
		MeshComp->UnHideBoneByName(BoneName);
	}
}
