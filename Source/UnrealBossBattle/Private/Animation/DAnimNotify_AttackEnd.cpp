// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_AttackEnd.h"
#include "DCharacter.h"
#include "DActionComponent.h"
#include "DAction_Attack.h"

void UDAnimNotify_AttackEnd::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ADCharacter* Character = Cast<ADCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		UDActionComponent* ActionComp = Character->GetComponentByClass<UDActionComponent>();
		if (ActionComp)
		{
			UDAction_Attack* AttackAction = Cast<UDAction_Attack>(ActionComp->GetAction(UDAction_Attack::StaticClass()));
			if (AttackAction)
			{
				if (AttackAction->IsRunning())
				{
					AttackAction->TryStopAction(Character);
				}
			}
		}
	}
}

