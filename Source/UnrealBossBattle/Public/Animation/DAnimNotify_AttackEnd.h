// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DAnimNotify_AttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBOSSBATTLE_API UDAnimNotify_AttackEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
