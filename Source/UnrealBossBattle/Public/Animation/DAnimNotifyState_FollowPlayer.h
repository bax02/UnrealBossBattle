// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DAnimNotifyState_FollowPlayer.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotifyState_FollowPlayer : public UAnimNotifyState
{
	GENERATED_BODY()

private:

	ACharacter* Character;

	AAIController* Controller;	
public:

	#if WITH_EDITORONLY_DATA
	bool ShouldFireInEditor() override { return false; };
	#endif

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
