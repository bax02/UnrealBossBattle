// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_EnableCollision.h"
#include "AI/DAICharacter.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void UDAnimNotify_EnableCollision::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		TArray<UActorComponent*> Components = Character->GetComponentsByTag(UCapsuleComponent::StaticClass(), "WeaponCollision");
		if (!Components.IsEmpty())
		{
			UCapsuleComponent* CapsuleComp = Cast<UCapsuleComponent>(Components[0]);
			if (CapsuleComp)
			{
				if (bChangeHitbox)
				{
					CapsuleComp->SetCapsuleHalfHeight(ExtendHitboxHalfHeight);
				}
				CapsuleComp->SetGenerateOverlapEvents(!bDisableCollision);
			}
		}
		
	}

}