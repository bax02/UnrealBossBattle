// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_HideMesh.h"

void UDAnimNotify_HideMesh::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	MeshComp->SetVisibility(false);
}
