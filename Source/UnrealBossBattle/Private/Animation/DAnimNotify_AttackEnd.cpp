// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_AttackEnd.h"
#include "DCharacter.h"
#include "DActionComponent.h"

void UDAnimNotify_AttackEnd::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ADCharacter* Character = Cast<ADCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		UDActionComponent* ActionComp = Character->GetComponentByClass<UDActionComponent>();
		if (ActionComp)
		{
			ActionComp->StopActionByName(Character, "Attack");
		}
	}
}

