// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotifyState_FollowPlayer.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

void UDAnimNotifyState_FollowPlayer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		Controller = Cast<AAIController>(Character->GetController());
		if (Controller)
		{
			APawn* TargetActor = UGameplayStatics::GetPlayerPawn(Character, 0);
			if (TargetActor)
			{
				Controller->SetFocus(TargetActor, EAIFocusPriority::Default);
			}
		}
	}
}

void UDAnimNotifyState_FollowPlayer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (Controller)
	{
		Controller->ClearFocus(EAIFocusPriority::Default);
	}
}
